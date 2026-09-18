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

#include "mem_alloc.h"

static int memBlock_create(memBlock_t *block, uint32_t size){
    block = (memBlock_t *)memPtr;

    block->size = size;
    block->nextBlock = NULL;

    tail->nextBlock = block;
    tail = block;

    /* update the ptr to next block's address*/
    memPtr += (size/sizeof(uint32_t) + MEMBLOCK_HEADER_SIZE + MEMBLOCK_PADDING);

    return ERRNO_SUCESS;
}

int memBlock_init(){
    head = (memBlock_t *)memPtr;

    head->size = 0;
    head->nextBlock = NULL;

    tail = head;

    /* update the ptr to next block's address*/
    memPtr += (MEMBLOCK_HEADER_SIZE + MEMBLOCK_PADDING);
    return ERRNO_SUCESS;    
}

int memBlock_alloc(void* ptr, uint32_t size){
    int errno = 0;
    memBlock_t *dummy = head;

    /*try to find available block*/
    while(dummy != NULL){
        /*found memory block with requested size;*/
        if(dummy->size >= size && dummy->free == 0){
            ptr = (void*)dummy;
        }
    }

    /*create new block*/
    errno = memBlock_create(dummy, size);
    ptr = (void*)dummy;

    return errno;
}

int memBlock_free(void* ptr){
    memBlock_t *block = (memBlock_t *)ptr;
    block->free = true;    
}

/** } End of mem_alloc*/
