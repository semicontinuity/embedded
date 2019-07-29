#ifndef COMM_BUTTONS_QUEUES__00_03__VARS__MEM_H
#define COMM_BUTTONS_QUEUES__00_03__VARS__MEM_H

#include <util/bitops.h>
#include <cpu/avr/asm.h>
#include <avr/io.h>

#define PINA    _SFR_IO8 (0x00)
#define DDRA    _SFR_IO8 (0x01)
#define PORTA   _SFR_IO8 (0x02)

DEFINE_BITVAR(
    comm_buttons__button0__event_pending,
    COMM_BUTTONS__BUTTON0__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON0__EVENT_PENDING__BIT
);
DEFINE_BITVAR(
    comm_buttons__button0__event_value,
    COMM_BUTTONS__BUTTON0__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON0__EVENT_VALUE__BIT
);

DEFINE_BITVAR(
    comm_buttons__button1__event_pending,
    COMM_BUTTONS__BUTTON1__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON1__EVENT_PENDING__BIT
);
DEFINE_BITVAR(
    comm_buttons__button1__event_value,
    COMM_BUTTONS__BUTTON1__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON1__EVENT_VALUE__BIT
);

DEFINE_BITVAR(
    comm_buttons__button2__event_pending,
    COMM_BUTTONS__BUTTON2__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON2__EVENT_PENDING__BIT
);
DEFINE_BITVAR(
    comm_buttons__button2__event_value,
    COMM_BUTTONS__BUTTON2__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON2__EVENT_VALUE__BIT
);

DEFINE_BITVAR(
    comm_buttons__button3__event_pending,
    COMM_BUTTONS__BUTTON3__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON3__EVENT_PENDING__BIT
);
DEFINE_BITVAR(
    comm_buttons__button3__event_value,
    COMM_BUTTONS__BUTTON3__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON3__EVENT_VALUE__BIT
);

#endif