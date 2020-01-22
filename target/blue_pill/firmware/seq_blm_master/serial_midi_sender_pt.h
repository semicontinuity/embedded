#include <Arduino.h>
#include <stdint.h>
#include <pt.h>
#include "sysex_handler_blm_callbacks.h"

#define TASK_MIDI_SENDER__REQUESTED_TX_BIT__ACK     (0U)
#define TASK_MIDI_SENDER__REQUESTED_TX_BIT__NACK    (1U)
#define TASK_MIDI_SENDER__REQUESTED_TX_BIT__LAYOUT  (2U)

volatile uint8_t task_midi_sender__requested_tx = 0U;
int (*task_midi_sender__current)(struct pt *pt) = NULL;
struct pt task_midi_sender__current_thread;

uint8_t led_state2 = 0;
uint8_t led_state = 0;

// Implementations of callbacks, defined in sysex_handler_blm_callbacks.h
// -----------------------------------------------------------------------------

void sysex_blm__handle_ping() {
    digitalWrite(PA5, 1);
    task_midi_sender__requested_tx |= (1U << TASK_MIDI_SENDER__REQUESTED_TX_BIT__ACK);
}

void sysex_blm__handle_invalid_command() {
    digitalWrite(PA1, 1);
    task_midi_sender__requested_tx |= (1U << TASK_MIDI_SENDER__REQUESTED_TX_BIT__NACK);
}

void sysex_blm__handle_request_layout_info() {
    task_midi_sender__requested_tx |= (1U << TASK_MIDI_SENDER__REQUESTED_TX_BIT__LAYOUT);
}


//region serial_midi_sender

static int task_midi_sender__ack__run(struct pt *pt) {
    PT_BEGIN(pt);

//    digitalWrite(PA5, 1);

    task_midi_sender__requested_tx &= ~(1U << TASK_MIDI_SENDER__REQUESTED_TX_BIT__ACK);
    PT_END(pt);
}

static int task_midi_sender__nack__run(struct pt *pt) {
    PT_BEGIN(pt);

    task_midi_sender__requested_tx &= ~(1U << TASK_MIDI_SENDER__REQUESTED_TX_BIT__NACK);
    PT_END(pt);
}

static int task_midi_sender__layout__run(struct pt *pt) {
    PT_BEGIN(pt);

//    digitalWrite(PA1, 1);

    task_midi_sender__requested_tx &= ~(1U << TASK_MIDI_SENDER__REQUESTED_TX_BIT__LAYOUT);
    PT_END(pt);
}



int task_midi_sender__run(void) {
    if (!task_midi_sender__current) {
//        digitalWrite(PA5, led_state2 = ~led_state2);


        if (task_midi_sender__requested_tx) {
//            digitalWrite(PA1, 1);
            if (task_midi_sender__requested_tx & (1U << TASK_MIDI_SENDER__REQUESTED_TX_BIT__ACK)) {
                task_midi_sender__current = task_midi_sender__ack__run;
//                digitalWrite(PA5, 1);
            } else if (task_midi_sender__requested_tx & (1U << TASK_MIDI_SENDER__REQUESTED_TX_BIT__NACK)) {
                task_midi_sender__current = task_midi_sender__nack__run;
            } else if (task_midi_sender__requested_tx & (1U << TASK_MIDI_SENDER__REQUESTED_TX_BIT__LAYOUT)) {
                task_midi_sender__current = task_midi_sender__layout__run;
            }
            PT_INIT(&task_midi_sender__current_thread);
        }
    } else {
//        digitalWrite(PA1, led_state = ~led_state);
//        digitalWrite(PA1, 1);
    }
//    if (PT_ENDED == (*task_midi_sender__current)(&task_midi_sender__current_thread)) {
//        task_midi_sender__current = NULL;
//    }
}

//endregion