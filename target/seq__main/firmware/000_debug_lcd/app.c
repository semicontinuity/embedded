#include <mios32.h>

#include <string.h>

#include "app.h"
# include <FreeRTOS.h>
# include <semphr.h>
#include <app_lcd.h>

/////////////////////////////////////////////////////////////////////////////
// global variables
/////////////////////////////////////////////////////////////////////////////
u8 app_din_testmode;

/////////////////////////////////////////////////////////////////////////////
// for optional debugging messages via MIDI
// should be enabled for this application!
/////////////////////////////////////////////////////////////////////////////
#define DEBUG_VERBOSE_LEVEL 1
#define DEBUG_MSG MIOS32_MIDI_SendDebugMessage
#define MAX_PATH 100


/////////////////////////////////////////////////////////////////////////////
// This hook is called after startup to initialize the application
/////////////////////////////////////////////////////////////////////////////
void APP_Init(void) {
    APP_LCD_Init(0);

    MIOS32_LCD_Clear();
    MIOS32_LCD_CursorSet(0, 0);
    MIOS32_LCD_PrintString("L0");
    MIOS32_LCD_CursorSet(0, 1);
    MIOS32_LCD_PrintString("L1");
    MIOS32_LCD_CursorSet(0, 2);
    MIOS32_LCD_PrintString("L2");
    MIOS32_LCD_CursorSet(0, 3);
    MIOS32_LCD_PrintString("L3");

    // initialize all LEDs
    MIOS32_BOARD_LED_Init(0xffffffff);

    s32 result = MIOS32_SDCARD_Init(0);
    if (result < 0) {
        MIOS32_BOARD_LED_Set(0x2, 0x1);
    }

#if DEBUG_VERBOSE_LEVEL >= 1
    // print welcome message on MIOS terminal
    DEBUG_MSG("\n");
    DEBUG_MSG("====================\n");
    DEBUG_MSG("%s\n", MIOS32_LCD_BOOT_MSG_LINE1);
    DEBUG_MSG("====================\n");
    DEBUG_MSG("\n");
#endif

    MIOS32_BOARD_LED_Set(0x4, 0x1);
}


/////////////////////////////////////////////////////////////////////////////
// This task is running endless in background
/////////////////////////////////////////////////////////////////////////////
void APP_Background(void) {
    // PWM modulate the status LED (this is a sign of life)
    u32 timestamp = MIOS32_TIMESTAMP_Get();
    MIOS32_BOARD_LED_Set(1, (timestamp % 20) <= ((timestamp / 100) % 10));
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a MIDI package has been received
/////////////////////////////////////////////////////////////////////////////
void APP_MIDI_NotifyPackage(mios32_midi_port_t port, mios32_midi_package_t midi_package) {
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called before the shift register chain is scanned
/////////////////////////////////////////////////////////////////////////////
void APP_SRIO_ServicePrepare(void) {
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called after the shift register chain has been scanned
/////////////////////////////////////////////////////////////////////////////
void APP_SRIO_ServiceFinish(void) {
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a button has been toggled
// pin_value is 1 when button released, and 0 when button pressed
/////////////////////////////////////////////////////////////////////////////
void APP_DIN_NotifyToggle(u32 pin, u32 pin_value) {
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when an encoder has been moved
// incrementer is positive when encoder has been turned clockwise, else
// it is negative
/////////////////////////////////////////////////////////////////////////////
void APP_ENC_NotifyChange(u32 encoder, s32 incrementer) {
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a pot has been moved
/////////////////////////////////////////////////////////////////////////////
void APP_AIN_NotifyChange(u32 pin, u32 pin_value) {
}
