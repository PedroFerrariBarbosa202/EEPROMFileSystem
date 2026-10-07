#ifndef INCLUDEeefseefs_deviceeefs_device.h_
#define INCLUDEeefseefs_deviceeefs_device.h_

#include "eefs/eefs.h"
#include "errno.h"

typedef struct eefs_api_t{
  error_t (*eefs_open)(void);
  error_t (*eefs_close)(void);
  error_t (*eefs_file_create)(file_descriptor_t *file, 
      const char *file_name, 
      uint32_t size);
  error_t (*eefs_file_open)(file_descriptor_t *file, 
      const char* name);
  error_t (*eefs_file_write)(file_descriptor_t *file, 
      const uint8_t* data, 
      uint32_t length);
  error_t (*eefs_file_read)(file_descriptor_t *file, 
      uint8_t* data, 
      uint32_t length);
  error_t (*eefs_file_read_chr)(file_descriptor_t *file, 
      char* chr);
}eefs_api_t;

typedef struct eefs_device_t{
  eefs_api_t *api;
}eefs_device_t;

static const struct eefs_api_t api_handle = {
  .eefs_open = fs_init,
  .eefs_close = fs_close,
  .eefs_file_create = file_create,
  .eefs_file_open = file_open,
  .eefs_file_write = file_write,
  .eefs_file_read = file_read,
  .eefs_file_read_chr = file_read_chr
};

static struct eefs_device_t device_handle = {
  .api = &api_handle,
};

struct eefs_device_t *get_eefs_device_handle(void){
  return &device_handle;
}

#endif  // INCLUDEeefseefs_deviceeefs_device.h_
