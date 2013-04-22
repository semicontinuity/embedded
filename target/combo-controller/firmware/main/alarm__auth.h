#ifndef __ALARM__AUTH_H
#define __ALARM__AUTH_H

#include <stdint.h>
#include <avr/eeprom.h>


struct alarm__auth__password {
    uint8_t length;
    uint8_t data[8];
};

extern EEMEM struct alarm__auth__password ee__alarm__auth__password;
extern struct alarm__auth__password alarm__auth__password;


inline static void alarm__auth__init(void) {
    eeprom_read_block(&alarm__auth__password, &ee__alarm__auth__password, sizeof(alarm__auth__password));
}

#endif
    