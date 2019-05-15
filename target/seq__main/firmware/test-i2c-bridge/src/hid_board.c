#include "hid_board.h"

// invoked by APP_MIDI_NotifyPackage
void APP_HIDBoard_Process_Event(mios32_midi_package_t midi_package)  {
    s32 status;
    if(midi_package.type == NoteOn && midi_package.velocity > 0)  {
        MIOS32_MIDI_SendDebugMessage("switch on all LEDs");
        u8 payload[4] = { 0xFF, 0xFF, 0xFF, 0xFF };
        status = i2c_send(IIC_PORT, MATRIX_MCU_IIC_ADDR, &payload[0], sizeof(payload));
    }
    else if((midi_package.type == NoteOff) || (midi_package.type == NoteOn && midi_package.velocity == 0))  {
        MIOS32_MIDI_SendDebugMessage("switch off all LEDs");
        u8 payload[4] = { 0x00, 0x00, 0x00, 0x00 };
        status = i2c_send(IIC_PORT, MATRIX_MCU_IIC_ADDR, &payload[0], sizeof(payload));
    }
    else {
        MIOS32_MIDI_SendDebugMessage("other midi package");
        status = 1; //not a package which we need to send via I2C
    }

    if(status < 0)
        MIOS32_MIDI_SendDebugMessage("WARNING: Could not send via I2C.\n");
}


static void TASK_HIDBoard_Scan(void *pvParameters)  {
    portTickType xLastExecutionTime;

    // Initialise the xLastExecutionTime variable on task entry
    xLastExecutionTime = xTaskGetTickCount();

    uint8_t buttonEvent;
    while(1)  {
        vTaskDelayUntil(&xLastExecutionTime, 50 / portTICK_RATE_MS);

        s32 status;
        if((status = i2c_receive(IIC_PORT, MATRIX_MCU_IIC_ADDR, (u8 *) &buttonEvent, sizeof(buttonEvent))) >= 0)  {
            // event is 0 when nothing has happened
            if (buttonEvent != 0) {
                uint8_t pressed = buttonEvent >= 'a';
                uint8_t button = pressed ? buttonEvent - 'a' : buttonEvent - 'A';
                APP_HIDBoard_NotifyToggle(button, pressed);
            }
        }
//        else {
//            MIOS32_MIDI_SendDebugMessage("WARNING: Could not receive via I2C.\n");
//        }
    }
}

void APP_HIDBoard_NotifyToggle(uint8_t button, uint8_t pressed) {
    int note_number = 60 + button;

    int velocity;
    if (pressed)
        velocity = 127;
    else
        velocity = 0;

    MIOS32_MIDI_SendNoteOn(MATRIX_MIDI_PORT, MATRIX_MIDI_CHN, note_number, velocity);
}

void APP_HIDBoard_Init(void)  {
    xTaskCreate(
        TASK_HIDBoard_Scan,
        (const portCHAR *) "HIDBoard_Scan",
        configMINIMAL_STACK_SIZE,
        NULL,
        PRIORITY_TASK_BUTTON_MATRIX_SCAN,
        NULL
    );
}
