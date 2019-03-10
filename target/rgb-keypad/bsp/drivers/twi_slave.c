#include "cpu/avr/twi.h"
#include "cpu/avr/util/vthreads.h"
#include "drivers/twi_slave.h"

#include "services/tx_ring_buffer.h"


#ifdef TWI__SLAVE__THREAD__IP__REG
register uint8_t *twi__slave__thread__ip asm(QUOTE(TWI__SLAVE__THREAD__IP__REG));
#else
volatile uint8_t* twi__slave__thread__ip;
#endif


void twi__slave__thread__init(void) {
    VT_INIT(twi__slave__thread, twi__slave__thread__ip);
}


void twi__slave__thread__start(void) {
    twi__slave__start(/*false*/true);
}


bool twi__slave__thread__is_runnable(void) {
    return twi__is_software_action_required();
}



/**
 * Converts a lowe nibble of a byte hex character.
 */
uint8_t formatter__nibble_to_hex_char(uint8_t value) {
    if (value > 9) value += ('A' - ('9' + 1));
    return (uint8_t) (value + '0');
}

/**
 * Converts a byte to 2 hex characters.
 */
uint16_t formatter__byte_to_hex_chars(const uint8_t value) {
    return (formatter__nibble_to_hex_char(value >> 4) << 8) | formatter__nibble_to_hex_char((uint8_t) (value & 0x0F));
}

inline void console__put(uint8_t c) {
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put(c);
    }
}

inline void console__println(void) {
    console__put('\r');
    console__put('\n');
}

inline void console__print_byte_as_hex(const uint8_t value) {
    uint16_t hex = formatter__byte_to_hex_chars(value);
    console__put((uint8_t)(hex >> 8));
    console__put((uint8_t)(hex & 0xFF));
}


void twi__slave__thread__run(void) {
    console__put('$');
    VT_BEGIN(twi__slave__thread, twi__slave__thread__ip);

            uint8_t status1 = twi__status__get();
            twi__continue(true, false);

            console__put('b');
            console__print_byte_as_hex(status1);
            console__println();

            if (status1 == TWI__STATUS__SLAVE_WRITE_ACKNOWLEDGED) {
                VT_YIELD_WITH_MARK(twi__slave__thread, twi__slave__thread__ip, DATA);
            } else {
                return;
            }

//            VT_YIELD_WITH_MARK_IF_TRUE_ELSE_REWIND(
//                status1 == TWI__STATUS__SLAVE_WRITE_ACKNOWLEDGED, twi__slave__thread, twi__slave__thread__ip, DATA
//            );

            console__put('w');

            uint8_t data = twi__data__get();
            uint8_t status2 = twi__status__get();
            twi__continue(true, false);

            console__print_byte_as_hex(status2);
            console__put(':');
            console__print_byte_as_hex(data);
            console__println();

            if (__builtin_expect(status2 == TWI__STATUS__SLAVE_RECEIVED_DATA_BYTE_ACKNOWLEDGED, 1)) {
                console__put('+');
                console__println();
                twi__slave__on_data_byte_received(data);
                VT_REWIND(twi__slave__thread, twi__slave__thread__ip);  // repeat: perhaps, receive more bytes
            }

            if (status2 == TWI__STATUS__SLAVE_STOP_OR_REPEATED_START) {
                console__put('.');
                console__println();
                twi__slave__on_data_reception_finished();
            } else {
                console__put('!');
                console__println();
                twi__slave__on_data_reception_aborted();
            }

            VT_GOTO(twi__slave__thread, twi__slave__thread__ip, BEGIN);

    VT_UNREACHEABLE_END(twi__slave__thread);
}
