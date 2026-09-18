/**
 * \brief memory allocation driver header
 *
 * \author Pedro Ferrari Barbosa <pedro.ferraribarbosa2007@gmail.com>
 *
 * \version 1.0
 *
 * \date 9/17/2026
 *
 * \defgroup mem_alloc MEM_ALLOC
 * \ingroup drivers
 * \{
 */
#ifndef DRIVER_MEM_ALLOC_H
#define DRIVER_MEM_ALLOC_H

#include "common_defines.h"
#include "driv_eeprom.h"

#define MEMBLOCK_HEADER_SIZE (sizeof(memBlock_t))
#define MEMBLOCK_PADDING (8)

typedef struct memBlock_t{
    uint32_t size;
    uint8_t free;
    struct memBlock_t *nextBlock;
}memBlock_t;

memBlock_t *head;
memBlock_t *tail;

uint32_t* memPtr = (uint32_t*)(EEPROM_HEADER_SIZE + EEPROM_PADDING);

/**
 * \brief creates a memory block and adds it to the 
 * 
 * \param block memory block to allocate
 *
 * \param size size in bytes of the new block
 *
 * \return pointer no memory block
 */
static int memBlock_create(memBlock_t *block, uint32_t size);

/**
 * \brief initiates the memory block linked list
 *
 * \return error code
 */
int memBlock_init();

/**
 * \brief allocates memory in the eeprom
 *
 * \param ptr pointer to allocate
 * 
 * \param size number of bytes to allocate
 *
 * \return error code
 */
int memBlock_alloc(void* ptr, uint32_t size);

/**
 * \brief frees memory in the eeprom
 *
 * \param ptr address to free
 *
 * \return error code
 */

int memBlock_free(void* ptr);

#endif
/** } End of mem_alloc*/
