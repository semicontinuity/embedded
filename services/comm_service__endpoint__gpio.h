#ifndef __COMM_SERVICE__ENDPOINT__GPIO_H
#define __COMM_SERVICE__ENDPOINT__GPIO_H

#include "kernel.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include CAN_H

#include "cpu/avr/asm.h"


inline static void comm_service__endpoint__gpio__handle_port_out(const uint8_t* data) {
#if GPIO__PA__OUT_MASK != 0
    PORTA = (data[0] & GPIO__PA__OUT_MASK) | (PORTA & ~GPIO__PA__OUT_MASK) ;
#endif
#if GPIO__PB__OUT_MASK != 0
    PORTB = (data[1] & GPIO__PB__OUT_MASK) | (PORTB & ~GPIO__PB__OUT_MASK) ;
#endif
#if GPIO__PC__OUT_MASK != 0
    PORTC = (data[2] & GPIO__PC__OUT_MASK) | (PORTC & ~GPIO__PC__OUT_MASK) ;
#endif
#if GPIO__PD__OUT_MASK != 0
    PORTD = (data[3] & GPIO__PD__OUT_MASK) | (PORTD & ~GPIO__PD__OUT_MASK) ;
#endif
}


inline static void comm_service__endpoint__gpio__handle_port_toggle(const uint8_t* data) {
#if GPIO__PA__OUT_MASK != 0
    PINA = (*data & GPIO__PA__OUT_MASK);
#endif
#if GPIO__PB__OUT_MASK != 0
    PINB = (*(data+1) & GPIO__PB__OUT_MASK);
#endif
#if GPIO__PC__OUT_MASK != 0
    PINC = (*(data+2) & GPIO__PC__OUT_MASK);
#endif
#if GPIO__PD__OUT_MASK != 0
    PIND = (*(data+3) & GPIO__PD__OUT_MASK);
#endif
}


inline static void comm_service__endpoint__gpio__handle_port_clear(const uint8_t* data) {
#if GPIO__PA__OUT_MASK != 0
    PORTA &= ~(data[0] & GPIO__PA__OUT_MASK);
#endif
#if GPIO__PB__OUT_MASK != 0
    PORTB &= ~(data[1] & GPIO__PB__OUT_MASK);
#endif
#if GPIO__PC__OUT_MASK != 0
    PORTC &= ~(data[2] & GPIO__PC__OUT_MASK);
#endif
#if GPIO__PD__OUT_MASK != 0
    PORTD &= ~(data[3] & GPIO__PD__OUT_MASK);
#endif
}


inline static void comm_service__endpoint__gpio__handle_port_set(const uint8_t* data) {
#if GPIO__PA__OUT_MASK != 0
    PORTA |= (data[0] & GPIO__PA__OUT_MASK);
#endif
#if GPIO__PB__OUT_MASK != 0
    PORTB |= (data[1] & GPIO__PB__OUT_MASK);
#endif
#if GPIO__PC__OUT_MASK != 0
    PORTC |= (data[2] & GPIO__PC__OUT_MASK);
#endif
#if GPIO__PD__OUT_MASK != 0
    PORTD |= (data[3] & GPIO__PD__OUT_MASK);
#endif
}


inline static void comm_service__endpoint__gpio__handle(const uint8_t is_get) {
    if (is_get) {
    }
    else {
        // handle PUT
        uint8_t slot = CANP_SLOT_BITS(kernel__frame.header.id);
        uint8_t *data = kernel__frame.data;
        FIX_POINTER(data);

        switch (slot) {
        case CANP_REPORT__GPIO__PORT_OUT:
            comm_service__endpoint__gpio__handle_port_out(data);
            break;
        case CANP_REPORT__GPIO__PORT_IN:
            comm_service__endpoint__gpio__handle_port_toggle(data);
            break;
        case CANP_REPORT__GPIO__PORT_CLEAR:
            comm_service__endpoint__gpio__handle_port_clear(data);
            break;
        case CANP_REPORT__GPIO__PORT_SET:
            comm_service__endpoint__gpio__handle_port_set(data);
            break;
        }
    }
}

#endif