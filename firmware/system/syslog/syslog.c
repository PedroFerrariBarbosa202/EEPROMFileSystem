#include "syslog.h"  
#include "string.h"                   

void syslog_setup(void){
    uart_setup();
}

void syslog_print(const char* str){
    uint32_t str_size = strlen(str);

    for(uint32_t i = 0; i < str_size; i++){
        uart_write_byte((uint8_t)str[i]);
    }
}

void syslog_log(const char* ev, const char* str){
    syslog_print(ev);
    syslog_print(str);
    syslog_print("\n\r");
}