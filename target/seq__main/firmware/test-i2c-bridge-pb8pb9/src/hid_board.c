#include "hid_board.h"

#define NOTE_OFFSET (60)

// invoked by APP_MIDI_NotifyPackage
void APP_HIDBoard_Process_Event(mios32_midi_package_t midi_package)  {
    s32 status;
    if(midi_package.type == NoteOn && midi_package.velocity > 0)  {
        u8 button = midi_package.note - NOTE_OFFSET;
        u8 board = button / 16;
        u8 button_index = button % 16;
        u8 payload[4] = {
            button_index,
            (midi_package.velocity & 3) << 6,
            ((midi_package.velocity >> 2) & 3) << 6,
            ((midi_package.velocity >> 4) & 3) << 6,
        };
        status = i2c_send(IIC_PORT, (HID_BOARD_IIC_BASE_ADDR + board) << 1, payload, sizeof(payload));
    }
    else if((midi_package.type == NoteOff) || (midi_package.type == NoteOn && midi_package.velocity == 0))  {
        u8 button = midi_package.note - NOTE_OFFSET;
        u8 board = button / 16;
        u8 button_index = button % 16;
        u8 payload[4] = {
            button_index,
            (midi_package.velocity & 3) << 6,
            ((midi_package.velocity >> 2) & 3) << 6,
            ((midi_package.velocity >> 4) & 3) << 6,
        };
        status = i2c_send(IIC_PORT, (HID_BOARD_IIC_BASE_ADDR + board) << 1, payload, sizeof(payload));
    }
    else {
        MIOS32_MIDI_SendDebugMessage("other midi package");
        status = 1; //not a package which we need to send via I2C
    }

    if(status < 0)
        MIOS32_MIDI_SendDebugMessage("WARNING: Could not send via I2C.\n");
}


void receive(int board) {
    uint8_t event;
    s32 status = -1;
    while (status < 0) {
        if ((status = i2c_receive(IIC_PORT, (HID_BOARD_IIC_BASE_ADDR + board) << 1, (u8 *) &event, sizeof(event))) >= 0) {
            // event is 0 when nothing has happened
            if (event != 0) {
                if (event & 0x80U) {
                    // button event
                    u8 pressed = event & 1U;    // bug in firmware, Pressed was supposed to have lower bit set to 0
                    u8 button = (event & 0x7FU) >> 1U;
//                    u8 column = button >> 2U;
//                    u8 row = button & 3U;
//                    u32 sr = MIOS32_SRIO_NUM_SR - 1 - ((board << 2U) + column);
//                    u32 pin = (sr << 3U) | row;
                    APP_HIDBoard_NotifyToggle(16 * board + button, pressed);
                }
            }
        } else {
            MIOS32_MIDI_SendDebugMessage("WARNING: Could not receive via I2C.\n");
        }
    }
}

static void TASK_HIDBoard_Scan(void *pvParameters)  {
    portTickType xLastExecutionTime;

    // Initialise the xLastExecutionTime variable on task entry
    xLastExecutionTime = xTaskGetTickCount();


    while(1)  {
        vTaskDelayUntil(&xLastExecutionTime, 10 / portTICK_RATE_MS);

        receive(0);
        receive(1);
        receive(2);
        receive(3);
    }
}


void APP_HIDBoard_NotifyToggle(uint8_t button, uint8_t pressed) {
    int note_number = NOTE_OFFSET + button;

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
