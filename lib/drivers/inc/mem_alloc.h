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
    uint8_t free;
    uint16_t memPtr;
    uint32_t size;

    uint16_t next;
}memBlock_t;

/**
 * \brief allocates memory in the eeprom
 *
 * \param ptr pointer to allocate
 * 
 * \param size number of bytes to allocate
 *
 * \return error code
 */
int memBlock_alloc(uint16_t* ptr, uint32_t size);

/**
 * \brief gets the address of the end of the block list in eepromm
 *
 * \return address
 */

uint16_t get_memPtr(void);

#endif
/** } End of mem_alloc*/
