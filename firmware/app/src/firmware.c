#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <string.h>

#include "system.h"
#include "common_defines.h"
#include "syslog.h"
#include "i2c.h"
#include "mem_alloc.h"
#include "driv_eeprom.h"

#define UART_PORT (GPIOA)
#define RX_PIN (GPIO3)
#define TX_PIN (GPIO2)

static void gpio_setup(void) {
  rcc_periph_clock_enable(RCC_GPIOA);

  // uart gpio setup
  gpio_mode_setup(UART_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, TX_PIN | RX_PIN);
  gpio_set_af(UART_PORT, GPIO_AF7, TX_PIN | RX_PIN);
}

int main(void)
{
    i2c_config_t config = {
        .clock_freq_mhz = 42,
        .speed_hz = i2c_speed_fm_400k
    };

    system_setup();
    gpio_setup();
    i2c_init(I2C1, config);
    syslog_init();

    syslog_print("\r\n-------------------------------------------\r\n");
    
    uint16_t addr;
    int error = memBlock_alloc(&addr, 128);

    system_delay(100);

    uint8_t tx_buffer = 0x47;
    driv_eeprom_write(addr, &tx_buffer, 1);
    
    system_delay(100);

    syslog_log(LOG_MT_INFO, "SENT VALUE");

    uint8_t rx_buffer;
    driv_eeprom_read(addr, &rx_buffer, 1);

    syslog_log(LOG_MT_INFO, "VALUE READ FROM MEMORY:");
    syslog_print_uint8(rx_buffer);
    for(;;);

    return ERRNO_SUCESS;
}
