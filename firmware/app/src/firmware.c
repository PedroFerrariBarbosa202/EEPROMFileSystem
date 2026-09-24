#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <string.h>
#include <stdio.h>

#include "system.h"
#include "common_defines.h"
#include "syslog.h"
#include "i2c.h"
#include "mem_alloc.h"
#include "driv_eeprom.h"
#include "file_system.h"

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

    if (errno != ERRNO_SUCCESS)
        return errno;

    syslog_log(LOG_MT_INFO, "created file");

    system_delay(1000);

    const uint8_t tx_buffer[] = "PEDRO IS COOL";

    errno = file_write(
        file,
        tx_buffer,
        sizeof(tx_buffer) - 1
    );

    system_delay(1000);

    if (errno != ERRNO_SUCCESS)
        return errno;

    syslog_log(LOG_MT_INFO, "wrote to file");
    
    system_delay(1000);

    uint8_t rx_buffer[128];

    errno = file_read(
        file,
        rx_buffer,
        128
    );

    system_delay(1000);


    if (errno != ERRNO_SUCCESS)
        return errno;

    system_delay(1000);

    syslog_log(LOG_MT_INFO, "read!");
    syslog_log(LOG_MT_INFO, (const char*)&rx_buffer);


    syslog_log(LOG_MT_INFO, "printing errno: ");
    
    char log_buffer[32];

    snprintf(log_buffer, sizeof(log_buffer), "errno = %d\r\n", errno);
    syslog_log(LOG_MT_INFO, log_buffer);

    for (;;);

    return ERRNO_SUCCESS;
}