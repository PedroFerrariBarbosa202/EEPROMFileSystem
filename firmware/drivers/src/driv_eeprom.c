/**
 * \brief eeprom driver implementation 
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

#include <string.h>
#include <libopencm3/stm32/i2c.h>

#include "driv_eeprom.h"
#include "i2c.h"

int driv_eeprom_write(const uint16_t addr, const uint8_t* tx_buf, uint32_t length){
    uint8_t write_buf[length + 2];
    write_buf[0] = (addr >> 8) & 0xFF;
    write_buf[1] = addr & 0xFF;

    memcpy((write_buf + 2), tx_buf, length);
    i2c_write(I2C_PORT_0, EEPROM_ADDR, write_buf, length + 2);   
    
    return ERRNO_SUCCESS;
}

int driv_eeprom_read(const uint16_t addr, uint8_t* rx_buf, uint32_t length){
    uint8_t read_buf[2];
    read_buf[0] = (addr >> 8) & 0xFF;
    read_buf[1] = addr & 0xFF;

    i2c_write(I2C_PORT_0, EEPROM_ADDR, read_buf, 2);
    i2c_read(I2C_PORT_0, EEPROM_ADDR, rx_buf, length);  
    
    return ERRNO_SUCCESS;
}


/** } End of eeprom*/
