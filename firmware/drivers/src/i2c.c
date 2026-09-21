/**
 * \brief i2c driver header
 *
 * \author Pedro Ferrari Barbosa
 *
 * \version 1.0
 *
 * \date 9/16/2026
 *
 * \defgroup i2c I2C
 * \ingroup Group
 * \{
 */


#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "i2c.h"
#include "errno.h"

int i2c_init(i2c_port_t port, i2c_config_t config){
    int err = 0;

    switch(config.speed_hz)
    {
        case i2c_speed_sm_100k:      break;
        case i2c_speed_fm_400k:      break;
        case i2c_speed_fmp_1m:       break;
        case i2c_speed_unknown:
        default:
        #if defined(CONFIG_DRIVERS_DEBUG_ENABLED) && (CONFIG_DRIVERS_DEBUG_ENABLED == 1)
            sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_MODULE_NAME, "Invalid transfer rate!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            err = -1;   /* Invalid transfer rate */
            break;
    }

    if (err == 0)
    {
        uint32_t base_address = UINT32_MAX;

        switch(port)
        {
            case I2C_PORT_0: {

                base_address = I2C1_BASE;

                rcc_periph_clock_enable(RCC_GPIOB);
                rcc_periph_clock_enable(RCC_I2C1);
                rcc_periph_reset_pulse(RST_I2C1);     

                gpio_mode_setup(GPIOB,
                                GPIO_MODE_AF,
                                GPIO_PUPD_PULLUP,
                                GPIO6 | GPIO7);

                gpio_set_output_options(GPIOB,
                                        GPIO_OTYPE_OD,
                                        GPIO_OSPEED_50MHZ,
                                        GPIO6 | GPIO7);

                gpio_set_af(GPIOB,
                            GPIO_AF4,
                            GPIO6 | GPIO7);

            } break;

            case I2C_PORT_1: {

                base_address = I2C2_BASE;

                rcc_periph_clock_enable(RCC_GPIOB);
                rcc_periph_clock_enable(RCC_I2C2);
                rcc_periph_reset_pulse(RST_I2C2);     

                gpio_mode_setup(GPIOB,
                                GPIO_MODE_AF,
                                GPIO_PUPD_NONE,
                                GPIO10 | GPIO11);

                gpio_set_output_options(GPIOB,
                                        GPIO_OTYPE_OD,
                                        GPIO_OSPEED_50MHZ,
                                        GPIO10 | GPIO11);

                gpio_set_af(GPIOB,
                            GPIO_AF4,
                            GPIO10 | GPIO11);

            } break;

            case I2C_PORT_2: {

                base_address = I2C3_BASE;

                rcc_periph_clock_enable(RCC_GPIOA);
                rcc_periph_clock_enable(RCC_GPIOB);
                rcc_periph_clock_enable(RCC_I2C3);
                rcc_periph_reset_pulse(RST_I2C3);     


                gpio_mode_setup(GPIOA,
                                GPIO_MODE_AF,
                                GPIO_PUPD_NONE,
                                GPIO8);

                gpio_set_output_options(GPIOA,
                                        GPIO_OTYPE_OD,
                                        GPIO_OSPEED_50MHZ,
                                        GPIO8);

                gpio_set_af(GPIOA,
                            GPIO_AF4,
                            GPIO8);

                gpio_mode_setup(GPIOB,
                                GPIO_MODE_AF,
                                GPIO_PUPD_NONE,
                                GPIO4);

                gpio_set_output_options(GPIOB,
                                        GPIO_OTYPE_OD,
                                        GPIO_OSPEED_50MHZ,
                                        GPIO4);

                gpio_set_af(GPIOB,
                            GPIO_AF4,
                            GPIO4);

            } break;

            default:{
                #if defined(CONFIG_DRIVERS_DEBUG_ENABLED) && (CONFIG_DRIVERS_DEBUG_ENABLED == 1)
                    sys_log_print_event_from_module(
                        SYS_LOG_ERROR,
                        I2C_MODULE_NAME,
                        "Invalid port!"
                    );

                    sys_log_new_line();
                #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
                err = -1;  
            }break;
        }

        if(err == 0){
            i2c_peripheral_disable(base_address);

            I2C_CR1(base_address) |= I2C_CR1_SWRST;
            I2C_CR1(base_address) &= ~I2C_CR1_SWRST;

            i2c_set_clock_frequency(base_address, config.clock_freq_mhz);
            i2c_set_speed(base_address, config.speed_hz, config.clock_freq_mhz);
            i2c_set_own_7bit_slave_address(base_address, I2C_SLAVE_OWN_7BIT_ADDR);
            i2c_enable_ack(base_address);

            i2c_peripheral_enable(base_address);
        }
    }

    return err;  
}

int i2c_write(i2c_port_t port, i2c_slave_adr_t adr, uint8_t *data, uint16_t len){
    int err = 0;

    uint32_t base_address = UINT32_MAX;

    switch(port)
    {
        case I2C_PORT_0:
            base_address = I2C1_BASE;
            break;
        case I2C_PORT_1:
            base_address = I2C2_BASE;
            break;
        case I2C_PORT_2:
            base_address = I2C3_BASE;
            break;
        default:
        #if defined(CONFIG_DRIVERS_DEBUG_ENABLED) && (CONFIG_DRIVERS_DEBUG_ENABLED == 1)
            sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_MODULE_NAME, "Invalid port!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            err = -1;   /* Invalid I2C port */
            return err;
    }

    i2c_transfer7(base_address, adr, data, len, NULL, 0);
    return err;
}

int i2c_read(i2c_port_t port, i2c_slave_adr_t adr, uint8_t *data, uint16_t len){
    int err = 0;

    uint32_t base_address = UINT32_MAX;

    switch(port)
    {
        case I2C_PORT_0:
            base_address = I2C1_BASE;
            break;
        case I2C_PORT_1:
            base_address = I2C2_BASE;
            break;
        case I2C_PORT_2:
            base_address = I2C3_BASE;
            break;
        default:
        #if defined(CONFIG_DRIVERS_DEBUG_ENABLED) && (CONFIG_DRIVERS_DEBUG_ENABLED == 1)
            sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_MODULE_NAME, "Invalid port!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            err = -1;   /* Invalid I2C port */
            return err;
    }

    i2c_transfer7(base_address, adr, NULL, 0, data, len);
    return err;
}

 /** } End of i2c*/
