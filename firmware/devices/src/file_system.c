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

 #include <string.h>

 #include "mem_alloc.h"
 #include "file_system.h"

 #define FILE_MAX_NAME_SIZE 64

 static int32_t inode_ctr = 0;
 static file_descriptor_t directory[MAX_FILES];

  int fs_init(){
    /*pull file descriptors from EEPROM*/
    driv_eeprom_read(FILE_DESCRIPTOR_START_ADDR, (uint8_t*)directory, MAX_FILES * sizeof(directory));
    return ERRNO_SUCCESS;
  }

  int fs_close(){
    /*put file descriptors from EEPROM*/
    driv_eeprom_write(FILE_DESCRIPTOR_START_ADDR, (uint8_t*)directory, MAX_FILES * sizeof(directory));
    return ERRNO_SUCCESS;
  }


int file_create(file_descriptor_t *file, const char *file_name, uint32_t size){
    int errno = ERRNO_SUCCESS;
    uint16_t mem_ptr;

    errno = memBlock_alloc(&mem_ptr, size);

    strncpy(file->file_name, file_name, FILE_MAX_NAME_SIZE - 1);
    file->file_name[FILE_MAX_NAME_SIZE - 1] = '\0';

    file->size = size;
    file->inode = inode_ctr++;
    file->memBlockPtr = mem_ptr;
    file->permission = 0;
    file->flags = 0;
    file->type = FILE_TYPE_ARCHIVE;

    directory[inode_ctr] = *file;

    return errno;
}

 int file_write(file_descriptor_t file, const uint8_t* data, uint32_t length){
    int errno = ERRNO_SUCCESS;
    memBlock_t memBlock;

    errno = driv_eeprom_read(file.memBlockPtr, (uint8_t *)&memBlock, sizeof(memBlock_t));
    
    system_delay(100);

    errno = driv_eeprom_write(memBlock.memPtr, data, length);

    return errno;
 }

 int file_read(file_descriptor_t file, uint8_t* data, uint32_t length){
    int errno = ERRNO_SUCCESS;
    memBlock_t memBlock;

    errno = driv_eeprom_read(file.memBlockPtr, (uint8_t *)&memBlock, sizeof(memBlock_t));

    system_delay(100);

    errno = driv_eeprom_read(memBlock.memPtr, data, length);

    return errno;
 }


/** } End of file_system*/
