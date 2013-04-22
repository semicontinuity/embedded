#ifndef __AUTH_SERVER_H
#define __AUTH_SERVER_H

#include <stdint.h>
#include <avr/eeprom.h>


struct auth_server__password {
    uint8_t length;
    uint8_t data[8];
};

extern EEMEM struct auth_server__password ee__auth_server__password;
extern struct auth_server__password auth_server__password;


inline static void auth_server__init(void) {
    eeprom_read_block(&auth_server__password, &ee__auth_server__password, sizeof(auth_server__password));
}

#endif
    