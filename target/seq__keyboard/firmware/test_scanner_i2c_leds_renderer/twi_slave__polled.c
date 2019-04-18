#include "cpu/avr/twi.h"
#include "cpu/avr/util/vthreads.h"
#include "twi_slave.h"
#include "twi_slave_callbacks.h"


#ifdef TWI__SLAVE__THREAD__IP__REG
register uint8_t *twi__slave__thread__ip asm(QUOTE(TWI__SLAVE__THREAD__IP__REG));
#else
volatile uint8_t* twi__slave__thread__ip;
#endif


void twi__slave__thread__init(void) {
    VT_INIT(twi__slave__thread, twi__slave__thread__ip);
}


void twi__slave__thread__start(void) {
    twi__slave__start(false);
}


bool twi__slave__thread__is_runnable(void) {
    return twi__is_software_action_required();
}


void twi__slave__thread__run(void) {
    VT_BEGIN(twi__slave__thread, twi__slave__thread__ip);

            uint8_t status1 = twi__status__get();
            twi__continue(true, false);

            VT_YIELD_WITH_MARK_IF_TRUE_ELSE_REWIND(
                status1 == TWI__STATUS__SLAVE_WRITE_ACKNOWLEDGED, twi__slave__thread, twi__slave__thread__ip, DATA
            );

            uint8_t data = twi__data__get();
            uint8_t status2 = twi__status__get();
            twi__continue(true, false);

            if (__builtin_expect(status2 == TWI__STATUS__SLAVE_RECEIVED_DATA_BYTE_ACKNOWLEDGED, 1)) {
                twi__slave__on_data_byte_received(data);
                VT_REWIND(twi__slave__thread, twi__slave__thread__ip);  // repeat: perhaps, receive more bytes
            }

            if (status2 == TWI__STATUS__SLAVE_STOP_OR_REPEATED_START) {
                twi__slave__on_data_reception_finished();
            } else {
                twi__slave__on_data_reception_aborted();
            }

            VT_GOTO(twi__slave__thread, twi__slave__thread__ip, BEGIN);

    VT_UNREACHEABLE_END(twi__slave__thread);
}
