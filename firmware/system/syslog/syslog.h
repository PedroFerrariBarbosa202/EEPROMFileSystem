#ifndef SYSLOG_H_
#define SYSLOG_H_

#include "uart.h"
#include "common_defines.h"

#define LOG_MT_INFO ("INFO: ")
#define LOG_MT_WARNING ("WARNING: ")
#define LOG_MT_ERROR ("ERROR: ")

void syslog_setup(void);
void syslog_print(const char* str);
void syslog_log(const char* ev, const char* str);

#endif // SYSLOG_H_