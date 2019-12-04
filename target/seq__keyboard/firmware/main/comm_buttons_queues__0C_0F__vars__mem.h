#ifndef COMM_BUTTONS_QUEUES__0C_0F__VARS__MEM_H
#define COMM_BUTTONS_QUEUES__0C_0F__VARS__MEM_H

#include <cpu/avr/asm_bit_var.h>
#include <avr/io.h>

#if defined(COMM_BUTTONS__0C_0F__EVENT_DATA__REG)
register volatile uint8_t comm_buttons__0c_0f__event_data asm(QUOTE(COMM_BUTTONS__0C_0F__EVENT_DATA__REG));
#endif


DEFINE_REG_BITVAR(
    comm_buttons__button12__event_pending,
    COMM_BUTTONS__BUTTON12__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON12__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button12__event_value,
    COMM_BUTTONS__BUTTON12__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON12__EVENT_VALUE__BIT
);

DEFINE_REG_BITVAR(
    comm_buttons__button13__event_pending,
    COMM_BUTTONS__BUTTON13__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON13__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button13__event_value,
    COMM_BUTTONS__BUTTON13__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON13__EVENT_VALUE__BIT
);

DEFINE_REG_BITVAR(
    comm_buttons__button14__event_pending,
    COMM_BUTTONS__BUTTON14__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON14__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button14__event_value,
    COMM_BUTTONS__BUTTON14__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON14__EVENT_VALUE__BIT
);

DEFINE_REG_BITVAR(
    comm_buttons__button15__event_pending,
    COMM_BUTTONS__BUTTON15__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON15__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button15__event_value,
    COMM_BUTTONS__BUTTON15__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON15__EVENT_VALUE__BIT
);


void comm_buttons__0c_0f__event_data__start(void) {
    comm_buttons__0c_0f__event_data = 0;
}

#endif