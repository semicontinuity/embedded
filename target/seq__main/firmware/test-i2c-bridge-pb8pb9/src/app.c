#include "app.h"

// called after start up
void APP_Init(void) {
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
}


static u32 counter;

// called when a MIDI package is received
void APP_MIDI_NotifyPackage(mios32_midi_port_t port, mios32_midi_package_t midi_package)  {
    MIOS32_MIDI_SendDebugMessage("received midi package");
    APP_HIDBoard_Process_Event(midi_package);
    ++counter;
}

// unused functions
void APP_MIDI_Tick(void) {}
