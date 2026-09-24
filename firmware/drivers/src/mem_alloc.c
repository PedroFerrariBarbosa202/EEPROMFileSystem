/**
 * \brief memory allocation driver implementation
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
#include "driv_eeprom.h"
#include "mem_alloc.h"

uint16_t memPtr = DATA_BLOCK_START_ADDR;
uint32_t blockPtr = ALLOC_BLOCK_START_ADDR;

static int memBlock_create(uint16_t* addr, uint32_t size){    
    memBlock_t block;
    block.size = size;
    block.free = true;
    block.memPtr = memPtr;

    block.next = blockPtr + sizeof(memBlock_t);
    
    /*'return' the address to the user*/
    *addr = blockPtr;

    driv_eeprom_write(blockPtr, (uint8_t*)&block, sizeof(memBlock_t));
    
    /* update the ptr to next address*/
    blockPtr += sizeof(memBlock_t);
    memPtr += (size + MEMBLOCK_PADDING);

    return ERRNO_SUCCESS;
}

int memBlock_alloc(uint16_t* ptr, uint32_t size){
    int errno = 0;

    /*create new block*/
    errno = memBlock_create(ptr, size);
    return errno;
}

uint16_t get_memPtr(void){
    return memPtr;
}

/** } End of mem_alloc*/
