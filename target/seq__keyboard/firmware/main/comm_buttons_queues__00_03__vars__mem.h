#ifndef COMM_BUTTONS_QUEUES__00_03__VARS__MEM_H
#define COMM_BUTTONS_QUEUES__00_03__VARS__MEM_H

#include <cpu/avr/asm_bit_var.h>
#include <avr/io.h>

#if defined(COMM_BUTTONS__00_03__EVENT_DATA__REG)
register volatile uint8_t comm_buttons__00_03__event_data asm(QUOTE(COMM_BUTTONS__00_03__EVENT_DATA__REG));
#endif

DEFINE_REG_BITVAR(
    comm_buttons__button0__event_pending,
    COMM_BUTTONS__BUTTON0__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON0__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button0__event_value,
    COMM_BUTTONS__BUTTON0__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON0__EVENT_VALUE__BIT
);

DEFINE_REG_BITVAR(
    comm_buttons__button1__event_pending,
    COMM_BUTTONS__BUTTON1__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON1__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button1__event_value,
    COMM_BUTTONS__BUTTON1__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON1__EVENT_VALUE__BIT
);

DEFINE_REG_BITVAR(
    comm_buttons__button2__event_pending,
    COMM_BUTTONS__BUTTON2__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON2__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button2__event_value,
    COMM_BUTTONS__BUTTON2__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON2__EVENT_VALUE__BIT
);

DEFINE_REG_BITVAR(
    comm_buttons__button3__event_pending,
    COMM_BUTTONS__BUTTON3__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON3__EVENT_PENDING__BIT
);
DEFINE_REG_BITVAR(
    comm_buttons__button3__event_value,
    COMM_BUTTONS__BUTTON3__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON3__EVENT_VALUE__BIT
);


void comm_buttons__00_03__event_data__start(void) {
    comm_buttons__00_03__event_data = 0;
}

#endif