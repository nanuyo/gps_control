#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <inttypes.h>

#ifndef PORTNAME
#define PORTNAME "/dev/ttyS1"
#endif

int serial_init(void);
int serial_config(void);
int serial_println(const char *, int);
void serial_readln(char *, int);
void serial_close(void);

#endif
