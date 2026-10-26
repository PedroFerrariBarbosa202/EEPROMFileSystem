/**
 * \brief i2c driver header
 *
 * \author Pedro Ferrari Barbosa <pedro.ferraribarbosa2007@gmail.com>
 *
 * \version 1.0
 *
 * \date 9/16/2026
 *
 * \defgroup i2c I2C
 * \ingroup Group
 * \{
 */

#ifndef DRIVER_I2C_H
#define DRIVER_I2C_H

#include <stdint.h>
#include <libopencm3/cm3/memorymap.h>
#include <libopencm3/stm32/i2c.h>
#include "errno.h"

#define I2C_MODULE_NAME         "I2C"

#define I2C_SLAVE_OWN_7BIT_ADDR      (0x00)

typedef enum
{
    I2C_PORT_0=0,       /**< I2C port 0. */
    I2C_PORT_1,         /**< I2C port 1. */
    I2C_PORT_2         /**< I2C port 2. */
} i2c_port_t;

typedef struct{
    uint32_t speed_hz;  /**< Transfer rate in bps (choose between 100k, 400k and 1m)*/
    uint32_t clock_freq_mhz;   /**< clock frequency in MHz*/
}i2c_config_t;

typedef uint8_t i2c_slave_adr_t;

/**
 * \brief init i2c device
 *
 * \param port i2c port to choose
 * 
 * \param config configuration struct for the i2c initialization
 *
 * \return void
 */
int i2c_init(i2c_port_t port, i2c_config_t config);

/**
 * \brief write data to i2c device
 *
 * \param port i2c port to choose
 * 
 * \param adr address of slave to write to
 *
 * \param data data buffer to write to slave
 * 
 * \param len length of data buffer
 * 
 * \return error code
 */
int i2c_write(i2c_port_t port, i2c_slave_adr_t adr, uint8_t *data, uint16_t len);

/**
 * \brief write data to i2c device
 *
 * \param port i2c port to choose
 * 
 * \param adr address of slave to write to
 *
 * \param data data buffer to write to slave
 * 
 * \param len length of data buffer
 * 
 * \return error code
 */
int i2c_read(i2c_port_t port, i2c_slave_adr_t adr, uint8_t *data, uint16_t len);

#endif
/** } End of i2c*/
