#include "device.h"

#include <avr/pgmspace.h>
#include <avr/io.h>

#include "cpu/avr/usart0.h"


const prog_uint8_t MESSAGE[]={
 'A','T','+','C','M','S','S','='
};


void sendSms(uint8_t index)
{
    prog_uint8_t* ptr = MESSAGE;
    prog_uint8_t* end = (prog_uint8_t*)(MESSAGE + sizeof(MESSAGE));
    while (ptr <= end)
    {
        usart__out__write(pgm_read_byte(ptr));
        ptr++;
    }
    usart__out__write(index);
    usart__out__write(10);
}
    