#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <string.h>
#include <stdio.h>

#include "eefs/eefs.h"

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

    int errno;

    system_setup();
    gpio_setup();

    i2c_init(I2C1, config);

    syslog_init();

    fs_init();

    syslog_print("\r\n-------------------------------------------\r\n");

    file_descriptor_t file;

    errno = file_create(&file, "pedro", 128);

    if (errno != ERRNO_SUCCESS) {
        syslog_log(LOG_MT_ERROR, "FAILED TO CREATE FILE");
        return errno;
    }

    errno = file_open(&file, "pedro");

    if (errno != ERRNO_SUCCESS) {
        syslog_log(LOG_MT_ERROR, "FAILED TO OPEN FILE");
        return errno;
    }

    syslog_log(LOG_MT_INFO, "created file");
    syslog_log(LOG_MT_INFO, "writing to file");

    const char *data = "Teste";

    errno = file_write(&file,
                       (uint8_t *)data,
                       strlen(data));

    if (errno != ERRNO_SUCCESS) {
        syslog_log(LOG_MT_ERROR, "FAILED TO WRITE FILE");
        return errno;
    }

    
    system_delay(100);

    syslog_log(LOG_MT_INFO, "reading from file");

    char chr;
    while (file_read_chr(&file, &chr) != ERRNO_EOF) {
        syslog_print_uint8((uint8_t)chr);
    }
    fs_close();

    for (;;);

    return ERRNO_SUCCESS;
}
