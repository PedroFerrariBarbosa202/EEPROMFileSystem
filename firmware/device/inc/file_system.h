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

 #define FILE_MAX_NAME_SIZE 64

 typedef struct file_t{
    uint16_t memBlockPtr;
    uint32_t pid;
    uint32_t size;
    char file_name[FILE_MAX_NAME_SIZE];
 }file_t;

 int file_create(const char* file_name);


/** } End of file_system*/
