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

#define EEPROM_HEADER_SIZE (sizeof(struct eeprom_headerBlock_t))
#define EEPROM_PADDING (8)


typedef struct eeprom_headerBlock_t{
    uint32_t size;
}eeprom_memBlock_t;

#endif
/** } End of eeprom*/
