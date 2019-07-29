#ifndef COMM_BUTTONS_QUEUES__04_07__VARS__MEM_H
#define COMM_BUTTONS_QUEUES__04_07__VARS__MEM_H

#include <util/bitops.h>
#include <cpu/avr/asm.h>
#include <avr/io.h>

#define PINA    _SFR_IO8 (0x00)
#define DDRA    _SFR_IO8 (0x01)
#define PORTA   _SFR_IO8 (0x02)


DEFINE_BITVAR(
    comm_buttons__button4__event_pending,
    COMM_BUTTONS__BUTTON4__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON4__EVENT_PENDING__BIT
);
DEFINE_BITVAR(
    comm_buttons__button4__event_value,
    COMM_BUTTONS__BUTTON4__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON4__EVENT_VALUE__BIT
);

DEFINE_BITVAR(
    comm_buttons__button5__event_pending,
    COMM_BUTTONS__BUTTON5__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON5__EVENT_PENDING__BIT
);
DEFINE_BITVAR(
    comm_buttons__button5__event_value,
    COMM_BUTTONS__BUTTON5__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON5__EVENT_VALUE__BIT
);

DEFINE_BITVAR(
    comm_buttons__button6__event_pending,
    COMM_BUTTONS__BUTTON6__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON6__EVENT_PENDING__BIT
);
DEFINE_BITVAR(
    comm_buttons__button6__event_value,
    COMM_BUTTONS__BUTTON6__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON6__EVENT_VALUE__BIT
);

DEFINE_BITVAR(
    comm_buttons__button7__event_pending,
    COMM_BUTTONS__BUTTON7__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON7__EVENT_PENDING__BIT
);
DEFINE_BITVAR(
    comm_buttons__button7__event_value,
    COMM_BUTTONS__BUTTON7__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON7__EVENT_VALUE__BIT
);


#endif