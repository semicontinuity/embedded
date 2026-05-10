// =============================================================================
// MODBUS RTU driver.
// USART module.
// =============================================================================

#include "buffer.h"
#include "modbus_rtu_driver__delay_timer.h"
#include "modbus_rtu_driver__usart.h"

#include "stm32f10x_conf.h"


volatile bool modbus_rtu_driver__usart_rx__enabled;


uint8_t usart0__getc() {
    return (uint8_t) USART_ReceiveData(USART1);
}

void usart0__rx__enabled__set(bool value) {
    USART_ITConfig(USART1, USART_IT_RXNE, value ? ENABLE : DISABLE);
}

void usart0__rx__complete__interrupt__enabled__set(bool value) {
    USART_ITConfig(USART1, USART_IT_RXNE, value ? ENABLE : DISABLE);
}

// =============================================================================

void modbus_rtu_driver__usart__init(void) {

}

void modbus_rtu_driver__usart__start(void) {
    modbus_rtu_driver__usart_rx__enable();
    usart0__rx__enabled__set(1);
    usart0__rx__complete__interrupt__enabled__set(1);

}

void modbus_rtu_driver__usart__stop(void) {
    modbus_rtu_driver__usart_rx__disable();
    usart0__rx__enabled__set(0);
    usart0__rx__complete__interrupt__enabled__set(0);
}



void modbus_rtu_driver__usart_rx__disable(void) {
    modbus_rtu_driver__usart_rx__enabled = false;
}


void modbus_rtu_driver__usart_rx__enable(void) {
    modbus_rtu_driver__usart_rx__enabled = true;
}


void modbus_rtu_driver__usart_rx__not_empty() {
    const uint8_t c = usart0__getc(); // read character in any case
    modbus_rtu_driver__delay_timer__start();
    if (modbus_rtu_driver__usart_rx__enabled) {
        if (!buffer__is_full()) {
            buffer__put_u8(c);
        }
        else {
            modbus_rtu_driver__usart_rx__on_buffer_overflow();            
        }
    }
    else {
        modbus_rtu_driver__usart_rx__on_unexpected_data();
    }
}



void modbus_rtu_driver__usart_tx__start(void) {
    usart0__tx__enabled__set(1);    
}


void modbus_rtu_driver__usart_tx__stop(void) {
    usart0__tx__enabled__set(0);    
}


void modbus_rtu_driver__usart_tx__signal(void) {
    usart0__tx__data_register_empty__interrupt__enabled__set(1);
}


void modbus_rtu_driver__usart_tx__empty() {
    if (!buffer__is_empty()) {
        usart0__putc(buffer__get_u8());
    }
    else {
        // Assuming, that this interrupt is handled fast enough,
        // so that the last bit is not completely transmitted yet.

        // Clear TX Complete flag by writing 1 (almost certainly it is set, and interrupt will be triggered immediately)
        // The TX Complete interrupt will be triggered when the byte is completely transmitted.
        usart0__tx__complete__value__set(1);
        usart0__tx__complete__interrupt__enabled__set(1);
        usart0__tx__data_register_empty__interrupt__enabled__set(0);    // prevent re-triggering
    }
}


void modbus_rtu_driver__usart_tx__completed() {
    usart0__tx__complete__interrupt__enabled__set(0);
    modbus_rtu_driver__usart_tx__on_frame_sent();   // in NAKED int, must not corrupt CPU state!
}


void USART1_IRQHandler(void) {
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
        modbus_rtu_driver__usart_rx__not_empty();
    }
    if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET) {
        USART_ClearITPendingBit(USART1, USART_IT_TXE);
        modbus_rtu_driver__usart_tx__empty();
    }
    if (USART_GetITStatus(USART1, USART_IT_TC) != RESET) {
        USART_ClearITPendingBit(USART1, USART_IT_TC);
        modbus_rtu_driver__usart_tx__completed();
    }
}
