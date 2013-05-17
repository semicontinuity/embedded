#ifndef __CPU__AVR__DRIVERS__DISPLAY__MT12232__TERMINAL_H
#define __CPU__AVR__DRIVERS__DISPLAY__MT12232__TERMINAL_H

#include <avr/pgmspace.h>


void terminal__putc(char c);

void terminal__print_P(const char * PROGMEM str);

#endif