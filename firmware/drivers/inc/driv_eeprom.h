/**
 * \brief eeprom driver header 
 *
 * \author Pedro Ferrari Barbosa <pedro.ferraribarbosa2007@gmail.com>
 *
 * \version 1.0
 *
 * \date 9/16/2026
 *
 * \defgroup eeprom EEPROM
 * \ingroup driver
 * \{
 */

#ifndef DRIVER_EEPROM_H
#define DRIVER_EEPROM_H

#include "common_defines.h"

#define EEPROM_ADDR (0x50)

#define SUPERBLOCK_SIZE (sizeof(struct superblock_t))

#define SUPERBLOCK_START_ADDR (0x0000)
#define FILE_DESCRIPTOR_START_ADDR (0x0100)
#define ALLOC_BLOCK_START_ADDR (0x0300)
#define DATA_BLOCK_START_ADDR (0x1000)

typedef struct superblock_t{
    uint32_t size;
}superblock_t;

int driv_eeprom_write(const uint16_t addr, const uint8_t* tx_buf, uint32_t length);
int driv_eeprom_read(const uint16_t addr, uint8_t* rx_buf, uint32_t length);

#endif
/** } End of eeprom*/
