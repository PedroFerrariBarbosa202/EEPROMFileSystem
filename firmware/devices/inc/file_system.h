/**
 * \brief file system header
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

 #include "mem_alloc.h"
 #include "file_metadata.h"
 #include "system.h"
 #include "common_defines.h"

 #define FS_MAGIC 0xcafe

 #define FILE_MAX_NAME_SIZE 64
 #define MAX_FILES 64

typedef struct superblock_t{
  uint32_t magic;
  uint32_t num_files;
}superblock_t;

 typedef struct file_descriptor_t{
    uint16_t memBlockPtr;

    uint32_t inode;

    uint32_t size;
    uint32_t length;
    uint32_t offset;

    uint8_t flags;
    uint8_t permission;
    uint8_t type;
    uint8_t deleted;
    
    char file_name[FILE_MAX_NAME_SIZE];
 }file_descriptor_t;

 int fs_init();
 int fs_close();

 int file_create(file_descriptor_t *file, const char *file_name, uint32_t size);
 int file_write(file_descriptor_t *file, const uint8_t* data, uint32_t length);
 int file_read(file_descriptor_t *file, uint8_t* data, uint32_t length);
 int file_read_chr(file_descriptor_t *file, char* chr);

 int file_open(file_descriptor_t *file, const char* name);


/** } End of file_system*/
