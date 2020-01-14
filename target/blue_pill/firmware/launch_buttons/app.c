// $Id$
/*
 * MIOS32 Tutorial #002: Parsing MIDI
 * see README.txt for details
 *
 * ==========================================================================
 *
 *  Copyright (C) 2009 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

/////////////////////////////////////////////////////////////////////////////
// Include files
/////////////////////////////////////////////////////////////////////////////

#include <mios32.h>
#include "app.h"

GPIO_InitTypeDef GPIO_InitStructure;


void initOutputPins0_7(GPIO_TypeDef *port) {
    /* Configure PA.0 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PA.1 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PA.2 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PA.3 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PA.4 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PA.5 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PA.6 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PA.7 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);
}


void initInputPins8_15(GPIO_TypeDef *port) {
    /* Configure PB.8 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PB.9 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PB.10 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PB.11 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PB.12 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PB.13 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PB.14 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PB.15 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);
}

/////////////////////////////////////////////////////////////////////////////
// This hook is called after startup to initialize the application
/////////////////////////////////////////////////////////////////////////////
void APP_Init(void) {
    // initialize all LEDs
    MIOS32_BOARD_LED_Init(0xffffffff);

    initOutputPins0_7(GPIOA);
    initInputPins8_15(GPIOB);
}


volatile uint8_t latest_buttons_state = 0xFFU;

void pad_reader__run() {
    uint16_t current_buttons_state = GPIO_ReadInputData(GPIOB) >> 8U;
    uint8_t diff = current_buttons_state ^ latest_buttons_state;
    if (diff) {
        MIOS32_MIDI_SendDebugMessage("KB: was %x, now %x\n", latest_buttons_state, current_buttons_state);
        for (uint8_t index = 0; index < 8; index++) {
            if (diff & (0x01U << index)) {
                MIOS32_MIDI_SendDebugMessage("Diff at %d\n", index);
//                mios32_midi_package_t midi_package;
//                midi_package.type = NoteOn;
//                midi_package.note = index;
//                midi_package.velocity = (current_buttons_state & (0x01U << index)) ? 0 : 0x7F;
//                MIOS32_MIDI_SendPackage(USB0, midi_package);
                MIOS32_MIDI_SendNoteOn(USB0, Chn1, index, (current_buttons_state & (0x01U << index)) ? 0 : 0x7F);
            }
        }
        latest_buttons_state = current_buttons_state;
    }
}



/////////////////////////////////////////////////////////////////////////////
// This task is running endless in background
/////////////////////////////////////////////////////////////////////////////
void APP_Background(void)
{
    for (;;) {
        pad_reader__run();
    }
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called each mS from the main task which also handles DIN, ENC
// and AIN events. You could add more jobs here, but they shouldn't consume
// more than 300 uS to ensure the responsiveness of buttons, encoders, pots.
// Alternatively you could create a dedicated task for application specific
// jobs as explained in $MIOS32_PATH/apps/tutorials/006_rtos_tasks
/////////////////////////////////////////////////////////////////////////////
void APP_Tick(void)
{
}

volatile uint16_t led_inc[8] = {0, 0, 0, 0, 0, 0, 0, 0};
volatile uint16_t led_duty[8] = {0, 0, 0, 0, 0, 0, 0, 0};


void led_set(u32 led, u32 value) {
    MIOS32_SYS_STM_PINSET(GPIOA, 0x0001U << led, value);
}

void render_led(u8 led, u8 phase) { led_set(led,  phase < (led_duty[led] >> 8U) ? 1 : 0); }

void adjust_led(u8 led) { led_duty[led] = ((uint16_t)(led_duty[led] + led_inc[led])) & 0x0FFFU; }

/////////////////////////////////////////////////////////////////////////////
// This hook is called each mS from the MIDI task which checks for incoming
// MIDI events. You could add more MIDI related jobs here, but they shouldn't
// consume more than 300 uS to ensure the responsiveness of incoming MIDI.
/////////////////////////////////////////////////////////////////////////////
void APP_MIDI_Tick(void)
{
    // PWM modulate the status LED (this is a sign of life)
    u32 timestamp = MIOS32_TIMESTAMP_Get();
    u8 phase = timestamp & 0x0FU;
    if (phase == 0) {
        adjust_led(0);
        adjust_led(1);
    }
    render_led(0, phase);
    render_led(1, phase);
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a MIDI package has been received
/////////////////////////////////////////////////////////////////////////////
void APP_MIDI_NotifyPackage(mios32_midi_port_t port, mios32_midi_package_t midi_package) {
//    MIOS32_MIDI_SendDebugMessage("Port:%02X  Type:%X  Evnt0:%02X  Evnt1:%02X  Evnt2:%02X\n",
//                                 port,
//                                 midi_package.type,
//                                 midi_package.evnt0, midi_package.evnt1, midi_package.evnt2);


    if (midi_package.type == NoteOn || midi_package.type == NoteOff) {
        if (midi_package.note >= 0 && midi_package.note < 7) {
            if (midi_package.type == NoteOn && midi_package.velocity > 0) {
//                    led_set(midi_package.note, 1);
                led_duty[midi_package.note] = (midi_package.velocity & 0x0FU) << 8U;
                MIOS32_MIDI_SendDebugMessage("Note: %d Duty: %d\n", midi_package.note, led_duty[midi_package.note]);

            } else if ((midi_package.type == NoteOff) ||
                       (midi_package.type == NoteOn && midi_package.velocity == 0)) {
//                led_set(midi_package.note, 0);
                led_duty[midi_package.note] = 0x00;
                MIOS32_MIDI_SendDebugMessage("Note: %d Duty: %d\n", midi_package.note, led_duty[midi_package.note]);
            }
        }
    } else if (midi_package.type == CC && midi_package.cc_number >= 0 && midi_package.cc_number <= 7) {
        led_inc[midi_package.cc_number] = midi_package.value;
    }
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called before the shift register chain is scanned
/////////////////////////////////////////////////////////////////////////////
void APP_SRIO_ServicePrepare(void)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called after the shift register chain has been scanned
/////////////////////////////////////////////////////////////////////////////
void APP_SRIO_ServiceFinish(void)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a button has been toggled
// pin_value is 1 when button released, and 0 when button pressed
/////////////////////////////////////////////////////////////////////////////
void APP_DIN_NotifyToggle(u32 pin, u32 pin_value)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when an encoder has been moved
// incrementer is positive when encoder has been turned clockwise, else
// it is negative
/////////////////////////////////////////////////////////////////////////////
void APP_ENC_NotifyChange(u32 encoder, s32 incrementer)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a pot has been moved
/////////////////////////////////////////////////////////////////////////////
void APP_AIN_NotifyChange(u32 pin, u32 pin_value)
{
}
