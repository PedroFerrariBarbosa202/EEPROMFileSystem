/**
 * \brief file system implementation
 *
 * \author Pedro Ferrari Barbosa <pedro.ferraribarbosa2007@gmail.com>
 *
 * \version 1.0
 *
 * \date 21/9/2026
 *
 * \defgroup file_system FILE_SYSTEM
 * \ingroup devices
 * \{
 */

#include <stdio.h>
#include <string.h>

#include "config.h"
#include "eefs_internal.h"
#include "mem_alloc.h"
#include <eefs/eefs.h>

#define FILE_MAX_NAME_SIZE 64

static const eefs_api_t api_handle = {.eefs_open = fs_init,
                                      .eefs_close = fs_close,
                                      .eefs_file_create = file_create,
                                      .eefs_file_open = file_open,
                                      .eefs_file_write = file_write,
                                      .eefs_file_read = file_read,
                                      .eefs_file_read_chr = file_read_chr,
                                      .eefs_file_exists = file_exists};

static const eefs_device_t device_handle = {.api = &api_handle};

const eefs_device_t *get_eefs_device_handle(void) { return &device_handle; }

static uint32_t inode_ctr = 0;
static uint32_t directory_ctr = 0;
static file_descriptor_t directory[MAX_FILES];

static error_t retrieve_directory_eeprom() {
  return driv_eeprom_read(FILE_DESCRIPTOR_START_ADDR, (uint8_t *)directory,
                          MAX_FILES * sizeof(file_descriptor_t));
}

static error_t return_directory_eeprom() {
  return driv_eeprom_write_page(FILE_DESCRIPTOR_START_ADDR,
                                (uint8_t *)directory,
                                MAX_FILES * sizeof(file_descriptor_t));
}

static error_t get_file_memBlock_data(file_descriptor_t *file, char *data,
                                      uint32_t length) {
  int errno = ERRNO_SUCCESS;
  memBlock_t memBlock;

  errno = driv_eeprom_read(file->memBlockPtr, (uint8_t *)&memBlock,
                           sizeof(memBlock_t));
  errno = driv_eeprom_read(memBlock.memPtr, data, length);
  return errno;
}

static error_t set_file_memBlock_data(file_descriptor_t *file, char *data,
                                      uint32_t length) {
  int errno = ERRNO_SUCCESS;
  memBlock_t memBlock;

  errno = driv_eeprom_read(file->memBlockPtr, (uint8_t *)&memBlock,
                           sizeof(memBlock_t));
  errno = driv_eeprom_write(memBlock.memPtr, data, length);
  return errno;
}

static error_t append_file_memBlock_data(file_descriptor_t *file, char *data,
                                         uint32_t length) {
  int errno = ERRNO_SUCCESS;
  memBlock_t memBlock;

  errno = driv_eeprom_read(file->memBlockPtr, (uint8_t *)&memBlock,
                           sizeof(memBlock_t));
  errno = driv_eeprom_write(memBlock.memPtr + file->write_offset, data, length);

  /*update file write offset*/
  file->write_offset += strlen(data);
  if (file->write_offset >= file->size) {
    file->write_offset = 0;
  }

  return errno;
}

static error_t find_file_in_dir(const char *file_name) {
  for (int i = 0; i < MAX_FILES; i++) {
    if (strcmp(file_name, directory[i].file_name) == 0) {
      return i;
    }
  }

  return -1;
}

static error_t set_file_directory(file_descriptor_t *file) {
  int indx = find_file_in_dir(file->file_name);

  if (indx == -1) {
    return ERRNO_NO_FILE_FOUND;
  }

  directory[indx] = *file;
  return ERRNO_SUCCESS;
}

error_t fs_init(void) {
  int errno = ERRNO_SUCCESS;
  file_descriptor_t buffer[MAX_FILES];
  errno = retrieve_directory_eeprom();

  for (uint32_t i = 0; i < MAX_FILES; i++) {
    if (directory[i].deleted == false) {
#if defined(DEBUG) && (DEBUG == 1)
      syslog_print("\n\r");
      syslog_log(LOG_MT_DEBUG, "file checked on initialization");
#endif
      buffer[directory_ctr++] = directory[i];
    }
  }

  memcpy(directory, buffer, sizeof(directory));
  return errno;
}

error_t fs_close(void) { return return_directory_eeprom(); }

error_t file_create(file_descriptor_t *file, const char *file_name,
                    uint32_t size) {
  int errno = ERRNO_SUCCESS;
  uint16_t mem_ptr;

  errno = memBlock_alloc(&mem_ptr, size);

  strncpy(file->file_name, file_name, FILE_MAX_NAME_SIZE - 1);
  file->file_name[FILE_MAX_NAME_SIZE - 1] = '\0';

  file->size = size;
  file->length = 0;
  file->inode = inode_ctr++;
  file->memBlockPtr = mem_ptr;
  file->read_offset = 0;
  file->write_offset = 0;
  file->permission = 0;
  file->flags = 0;
  file->deleted = 0;
  file->type = 0;

  directory[directory_ctr++] = *file;

  return errno;
}

error_t file_write(file_descriptor_t *file, const uint8_t *data,
                   uint32_t length) {
  int errno = ERRNO_SUCCESS;

  errno = set_file_memBlock_data(file, (char *)data, length);
  file->length = length;

  set_file_directory(file);
  return errno;
}

error_t file_append(file_descriptor_t *file, const uint8_t *data,
                    uint32_t length) {
  int errno = ERRNO_SUCCESS;

  errno = append_file_memBlock_data(file, (char *)data, length);
  file->length += length;

  set_file_directory(file);
  return errno;
}

error_t file_read(file_descriptor_t *file, uint8_t *data, uint32_t length) {
  int errno = ERRNO_SUCCESS;

  errno = get_file_memBlock_data(file, (char *)data, length);

  return errno;
}

error_t file_read_chr(file_descriptor_t *file, char *chr) {
  int errno = ERRNO_SUCCESS;
  memBlock_t memBlock;
  char buff;

  if (file->read_offset >= file->length) {
    file->read_offset = 0;
    return ERRNO_EOF;
  }

  errno = driv_eeprom_read(file->memBlockPtr, (uint8_t *)&memBlock,
                           sizeof(memBlock_t));
  errno = driv_eeprom_read(memBlock.memPtr + file->read_offset,
                           (uint8_t *)&buff, 1);
  file->read_offset++;

  *chr = buff;
  return errno;
}

error_t file_open(file_descriptor_t *file, const char *name) {
  int indx = find_file_in_dir(name);

  if (indx == -1) {
    return ERRNO_NO_FILE_FOUND;
  }
  *file = directory[indx];

  return ERRNO_SUCCESS;
}

error_t file_exists(const char *file_name) {
  int indx = find_file_in_dir(file_name);

  if (indx == -1) {
    return ERRNO_NO_FILE_FOUND;
  }
  return ERRNO_SUCCESS;
}

/** } End of file_system*/
