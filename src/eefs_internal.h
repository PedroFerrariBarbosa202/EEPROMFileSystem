#ifndef EEFS_INTERNAL_H
#define EEFS_INTERNAL_H

#include <eefs/eefs.h>
#include <stdint.h>

/* Internal filesystem metadata */
typedef struct {
  uint32_t magic;
  uint32_t num_files;
} eefs_superblock_t;

/* Internal filesystem operations */
error_t fs_init(void);
error_t fs_close(void);

error_t file_create(file_descriptor_t *file, const char *file_name,
                    uint32_t size);

error_t file_open(file_descriptor_t *file, const char *name);

error_t file_write(file_descriptor_t *file, const uint8_t *data,
                   uint32_t length);

error_t file_append(file_descriptor_t *file, const uint8_t *data,
                    uint32_t length);

error_t file_read(file_descriptor_t *file, uint8_t *data, uint32_t length);

error_t file_read_chr(file_descriptor_t *file, char *chr);

error_t file_exists(const char *file_name);

#endif
