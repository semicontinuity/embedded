#ifndef COMM_BUTTONS_QUEUES__04_07__VARS__MEM_H
#define COMM_BUTTONS_QUEUES__04_07__VARS__MEM_H

#include <cpu/avr/asm_bit_var.h>
#include <avr/io.h>

#if defined(COMM_BUTTONS__04_07__EVENT_DATA__REG)
register volatile uint8_t comm_buttons__04_07__event_data asm(QUOTE(COMM_BUTTONS__04_07__EVENT_DATA__REG));
#endif

DEFINE_REG_BITVAR(
    comm_buttons__button4__event_pending,
    COMM_BUTTONS__BUTTON4__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON4__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button4__event_value,
    COMM_BUTTONS__BUTTON4__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON4__EVENT_VALUE__BIT
);

DEFINE_REG_BITVAR(
    comm_buttons__button5__event_pending,
    COMM_BUTTONS__BUTTON5__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON5__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button5__event_value,
    COMM_BUTTONS__BUTTON5__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON5__EVENT_VALUE__BIT
);

DEFINE_REG_BITVAR(
    comm_buttons__button6__event_pending,
    COMM_BUTTONS__BUTTON6__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON6__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button6__event_value,
    COMM_BUTTONS__BUTTON6__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON6__EVENT_VALUE__BIT
);

DEFINE_REG_BITVAR(
    comm_buttons__button7__event_pending,
    COMM_BUTTONS__BUTTON7__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON7__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button7__event_value,
    COMM_BUTTONS__BUTTON7__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON7__EVENT_VALUE__BIT
);


void comm_buttons__04_07__event_data__start(void) {
    comm_buttons__04_07__event_data = 0;
}

#endif