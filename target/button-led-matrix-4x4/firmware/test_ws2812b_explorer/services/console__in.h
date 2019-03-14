#ifndef __SERVICES__CONSOLE_IN_H
#define __SERVICES__CONSOLE_IN_H


#include <stdint.h>

#define CONSOLE__BUFFER_LENGTH 127

extern uint8_t console__input_buffer[CONSOLE__BUFFER_LENGTH];
extern volatile uint16_t console__input_length;


void console__in__init(void);

void console__in__start(void);

void console__read_line(void);


#endif