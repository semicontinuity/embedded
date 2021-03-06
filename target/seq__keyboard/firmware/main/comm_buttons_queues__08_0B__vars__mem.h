#ifndef COMM_BUTTONS_QUEUES__08_0B__VARS__MEM_H
#define COMM_BUTTONS_QUEUES__08_0B__VARS__MEM_H

#include <cpu/avr/asm_bit_var.h>
#include <avr/io.h>

#if defined(COMM_BUTTONS__08_0B__EVENT_DATA__REG)
register volatile uint8_t comm_buttons__08_0b__event_data asm(QUOTE(COMM_BUTTONS__08_0B__EVENT_DATA__REG));
#endif


DEFINE_REG_BITVAR(
    comm_buttons__button8__event_pending,
    COMM_BUTTONS__BUTTON8__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON8__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button8__event_value,
    COMM_BUTTONS__BUTTON8__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON8__EVENT_VALUE__BIT
);

DEFINE_REG_BITVAR(
    comm_buttons__button9__event_pending,
    COMM_BUTTONS__BUTTON9__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON9__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button9__event_value,
    COMM_BUTTONS__BUTTON9__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON9__EVENT_VALUE__BIT
);

DEFINE_REG_BITVAR(
    comm_buttons__button10__event_pending,
    COMM_BUTTONS__BUTTON10__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON10__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button10__event_value,
    COMM_BUTTONS__BUTTON10__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON10__EVENT_VALUE__BIT
);

DEFINE_REG_BITVAR(
    comm_buttons__button11__event_pending,
    COMM_BUTTONS__BUTTON11__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON11__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button11__event_value,
    COMM_BUTTONS__BUTTON11__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON11__EVENT_VALUE__BIT
);


void comm_buttons__08_0b__event_data__start(void) {
    comm_buttons__08_0b__event_data = 0;
}

#endif