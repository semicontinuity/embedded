#include "app.h"
#include "terminal.h"
#include "i2c_comm.h"


s32 APP_SYSEX_Parser(mios32_midi_port_t port, u8 midi_in) {
// SysEx would have to be handled by separate parser
// see $MIOS32_PATH/apps/controllers/midio128 as example
    return 0; // no error
}

void APP_Init(void) {
    // install SysEx callback
    MIOS32_MIDI_SysExCallback_Init(APP_SYSEX_Parser);

    TERMINAL_Init(0);

    I2C_Comm_Init(0);
}

// endless background task
void APP_Background(void) {
    MIOS32_MIDI_SendDebugMessage("started.");
    I2C_Comm_Idle();
    while (1);
}

// called each ms after scanning the inputs
void APP_Tick(void) {
}


// called when a MIDI package is received
void APP_MIDI_NotifyPackage(mios32_midi_port_t port, mios32_midi_package_t midi_package) {
    MIOS32_MIDI_SendDebugMessage("received midi package");
//    APP_HIDBoard_Process_Event(midi_package);
}

// unused functions
void APP_MIDI_Tick(void) {}
