// $Id$
/*
 * MIOS32 Tutorial #020: LCD Output
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
#include <string.h>
#include <stdarg.h>
#include <LCD.h>
#include "seq_terminal.h"


/////////////////////////////////////////////////////////////////////////////
// This hook is called after startup to initialize the application
/////////////////////////////////////////////////////////////////////////////
void APP_Init(void) {
    // initialize all LEDs
    MIOS32_BOARD_LED_Init(0xffffffff);
    SEQ_TERMINAL_Init(0);

    lcd_init(); 
    lcd_clear();
    lcd_print("Hello, world!");
}


/////////////////////////////////////////////////////////////////////////////
// This task is running endless in background
/////////////////////////////////////////////////////////////////////////////
void APP_Background(void)
{
    while (1) {}
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

  // PWM modulate the status LED (this is a sign of life)
  u32 timestamp = MIOS32_TIMESTAMP_Get();
  MIOS32_BOARD_LED_Set(1, (timestamp % 20) <= ((timestamp / 100) % 10));
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called each mS from the MIDI task which checks for incoming
// MIDI events. You could add more MIDI related jobs here, but they shouldn't
// consume more than 300 uS to ensure the responsiveness of incoming MIDI.
/////////////////////////////////////////////////////////////////////////////
void APP_MIDI_Tick(void)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a MIDI package has been received
/////////////////////////////////////////////////////////////////////////////
void APP_MIDI_NotifyPackage(mios32_midi_port_t port, mios32_midi_package_t midi_package)
{
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

/////////////////////////////////////////////////////////////////////////////
// Send a Mutex protected debug messages (referenced by DEBUG_MSG macro)
/////////////////////////////////////////////////////////////////////////////
void APP_SendDebugMessage(char *format, ...)
{
//    MUTEX_MIDIOUT_TAKE;
    
    {
    char str[128]; // 128 chars allowed
    va_list args;
    
    // failsave: if format string is longer than 100 chars, break here
    // note that this is a weak protection: if %s is used, or a lot of other format tokens,
    // the resulting string could still lead to a buffer overflow
    // other the other hand we don't want to allocate too many byte for buffer[] to save stack
    if( strlen(format) > 100 ) {
        // exit with less costly message
        MIOS32_MIDI_SendDebugString("(ERROR: string passed to MIOS32_MIDI_SendDebugMessage() is longer than 100 chars!\n");
    } else {
        // transform formatted string into string
        va_start(args, format);
        vsprintf(str, format, args);
    }
    
    u32 len = strlen(str);
    u8 *str_ptr = (u8 *)str;
    int i;
    for(i=0; i<len; ++i) {
        *str_ptr++ &= 0x7f; // ensure that MIDI protocol won't be violated
    }
    
    MIOS32_MIDI_SendDebugString(str);
    }
    
//MUTEX_MIDIOUT_GIVE;
}
