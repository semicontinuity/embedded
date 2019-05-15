#include "app.h"

// called after start up
void APP_Init(void) {
    // initialize all LEDs
    MIOS32_BOARD_LED_Init(0xffffffff);

    MIOS32_IIC_Init(0); //I2C connection is for example used to communicate with the button matrix MCU

    // start processing tasks
    APP_HIDBoard_Init();
}

// endless background task
void APP_Background(void)  {
    MIOS32_MIDI_SendDebugMessage("test-i2c-bridge started.");
    while(1);
}

// called each ms after scanning the inputs
void APP_Tick(void)  {
    // PWM modulate the status LED (this is a sign of life)
    u32 timestamp = MIOS32_TIMESTAMP_Get();
    MIOS32_BOARD_LED_Set(1, (timestamp % 20) <= ((timestamp / 100) % 10));
}

static u32 counter;
// called when a MIDI package is received
void APP_MIDI_NotifyPackage(mios32_midi_port_t port, mios32_midi_package_t midi_package)  {
    MIOS32_BOARD_LED_Set(2, counter << 1U); // will toggle LED2 on each MIDI package
    MIOS32_MIDI_SendDebugMessage("received midi package");
    APP_HIDBoard_Process_Event(midi_package);
    ++counter;
}

// unused functions
void APP_MIDI_Tick(void) {}
