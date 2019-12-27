// Mapping of HID boards to SRIO lines:
//
// SRIO 0-3:    Board @I2C 0x23 (rightmost)
// SRIO 4-7:    Board @I2C 0x22
// SRIO 8-11:   Board @I2C 0x21
// SRIO 12-15:  Board @I2C 0x20 (leftmost)
// SRIO 16-19:  Board @I2C 0x30 (keypad)
// SRIO 20-23:  Virtual SRIO for GP keys (R Color 1, L Color 1, R Color 2, L Color 2)
// SRIO 24-27:  Virtual SRIO for TRACK keys (R Color 1, L Color 1, R Color 2, L Color 2)
#include <mios32.h>

// this module can be optionally disabled in a local mios32_config.h file (included from mios32.h)
#if defined(SEQ_USE_MOD)

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include "seq_mod.h"
#include "app.h"
#include "seq_hwcfg.h"

#define PRIORITY_TASK_SCAN_HID_BOARDS (tskIDLE_PRIORITY + 3)

#include <string.h>

static volatile u32 transpose_enabled = 0;
static volatile u32 i2c_reading_enabled = 0;
static volatile u8 i2c_event = 0;


void SEQ_Mod_SendLedValues() {
    u8 *buffer = (u8 *) &mios32_srio_dout[0][0];
    u8 address = MIOS32_IIC_IO_BASE_ADDRESS;
    while (address < MIOS32_IIC_IO_BASE_ADDRESS + MIOS32_IIC_IO_BOARDS) {
        s32 error = MIOS32_IIC_Transfer(MIOS32_IIC_IO_PORT, IIC_Write, address << 1U, buffer, MIOS32_IIC_IO_ROWS_PER_BOARD);
        if (!error)
            MIOS32_IIC_TransferWait(MIOS32_IIC_IO_PORT);
        ++address;
        buffer += MIOS32_IIC_IO_ROWS_PER_BOARD;
    }
}


int encoder_value[SEQ_HWCFG_NUM_ENCODERS];
int encoder_reported_value[SEQ_HWCFG_NUM_ENCODERS];

// Because of detented encoders, normally, packs of 4 events are received.
// Convert these "low-level" events to "high-level" delta events: 1 event per pack.
void handleEncoderEvent(u8 encoder_index, s8 delta) {
    int new_value = encoder_value[encoder_index] + delta;
    int new_reported_value = new_value / 4;
    int prev_reported_value = encoder_reported_value[encoder_index];
    if (new_reported_value != prev_reported_value) {
        // GP encoders are 1..16
        APP_ENC_NotifyChange(encoder_index + 1, new_reported_value - prev_reported_value);
        encoder_reported_value[encoder_index] = new_reported_value;
    }
    encoder_value[encoder_index] = new_value;
}

void handleEvent(u8 board, u8 event) {
    if (event & 0x80U) {
        // button event
        u8 pressed = event & 1U;    // bug in firmware, Pressed was supposed to have lower bit set to 0
        u8 button = (event & 0x7FU) >> 1U;
        u8 column = button >> 2U;
        u8 row = button & 3U;
        u32 sr = 16 - 1 - ((board << 2U) + column);
        u32 pin = (sr << 3U) | row;
        APP_DIN_NotifyToggle(pin,pressed ? 0 : 1);
    } else {
        // encoder event
        u8 delta_bits = (event & 0x1FU);
        u8 encoder = event >> 5U;
        s8 delta = delta_bits < 16 ? delta_bits : delta_bits - 32;
        handleEncoderEvent((board << 2U) + encoder, delta);
    }
}


s32 i2c_transfer(u8 port, u8 iic_addr, u8 *buffer, size_t size, mios32_iic_transfer_t transfer_type) {
    s32 status;

    if((status=MIOS32_IIC_TransferBegin(port, IIC_Blocking)) < 0)
        MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_TransferBegin failed with %d!\n", port, status);
    else {
        if((status=MIOS32_IIC_Transfer(port, transfer_type, iic_addr, buffer, size)) < 0)
            MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_Transfer failed with %d!\n", port, status);
        else {
            if((status=MIOS32_IIC_TransferWait(port)) < 0)
                MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_TransferWait failed with %d!\n", port, status);
            else
                MIOS32_IIC_TransferFinished(port);
        }
    }

    return status;
}

void receive(int board) {
    uint8_t event;
    s32 status = -1;
    while (status < 0) {
        if ((status = i2c_transfer(
                MIOS32_IIC_IO_PORT,
                (MIOS32_IIC_IO_BASE_ADDRESS + board) << 1,
                (u8 *) &event,
                sizeof(event),
                IIC_Read)) >= 0)
        {
            // event is 0 when nothing has happened
            if (event != 0) {
                if (event & 0x80U) {
                    // button event
                    u8 pressed = event & 1U;    // bug in firmware, Pressed was supposed to have lower bit set to 0
                    u8 button = (event & 0x7FU) >> 1U;
                    u8 column = button >> 2U;
                    u8 row = button & 3U;
                    u32 sr = 16 - 1 - ((board << 2U) + column);
                    u32 pin = (sr << 3U) | row;
                    APP_DIN_NotifyToggle(pin,pressed ? 0 : 1);
                } else {
                    // encoder event
                    u8 delta_bits = (event & 0x1FU);
                    u8 encoder = event >> 5U;
                    s8 delta = delta_bits < 16 ? delta_bits : delta_bits - 32;
                    handleEncoderEvent((board << 2U) + encoder, delta);
                }
            }
        } else {
            MIOS32_MIDI_SendDebugMessage("WARNING: Could not receive via I2C.\n");
        }
    }
}


void send(u8 board) {
    volatile u8 *buffer = (volatile u8 *) &mios32_srio_dout[0][0] + MIOS32_SRIO_NUM_SR - 16;
    i2c_transfer(
            MIOS32_IIC_IO_PORT,
            (MIOS32_IIC_IO_BASE_ADDRESS + board) << 1,
            buffer + (board * MIOS32_IIC_IO_ROWS_PER_BOARD),
            MIOS32_IIC_IO_ROWS_PER_BOARD,
            IIC_Write);
}

void transpose(u8 src_srio, u8 dst_srio, u8 bit) {
    u8 value = mios32_srio_dout[0][MIOS32_SRIO_NUM_SR - src_srio - 1];
    u8 *dst = &mios32_srio_dout[0][MIOS32_SRIO_NUM_SR - dst_srio - 1];
    u8 set_mask = 1U << bit;
    u8 clear_mask = ~set_mask;

    if (value & 1U) *dst |= set_mask; else *dst &= clear_mask;
    --dst;
    value >>= 1U;

    if (value & 1U) *dst |= set_mask; else *dst &= clear_mask;
    --dst;
    value >>= 1U;

    if (value & 1U) *dst |= set_mask; else *dst &= clear_mask;
    --dst;
    value >>= 1U;

    if (value & 1U) *dst |= set_mask; else *dst &= clear_mask;
    --dst;
    value >>= 1U;

    if (value & 1U) *dst |= set_mask; else *dst &= clear_mask;
    --dst;
    value >>= 1U;

    if (value & 1U) *dst |= set_mask; else *dst &= clear_mask;
    --dst;
    value >>= 1U;

    if (value & 1U) *dst |= set_mask; else *dst &= clear_mask;
    --dst;
    value >>= 1U;

    if (value & 1U) *dst |= set_mask; else *dst &= clear_mask;
}



static void TASK_CommunicateWithHIDBoards(void *pvParameters)  {
    portTickType xLastExecutionTime;

    // Initialise the xLastExecutionTime variable on task entry
    xLastExecutionTime = xTaskGetTickCount();


    while(1)  {
        vTaskDelayUntil(&xLastExecutionTime, 10 / portTICK_RATE_MS);

        receive(0);
        receive(1);
        receive(2);
        receive(3);

        if (transpose_enabled) {
            // Bits: 0=round buttons; 2,3,4=Tracks B,G,R; 5,6,7=GP B,G,R
            transpose(20, 0, 6);
            transpose(21, 8, 6);
            transpose(22, 0, 5);
            transpose(23, 8, 5);
            transpose(24, 0, 3);
            transpose(25, 8, 3);
            transpose(26, 0, 2);
            transpose(27, 8, 2);
        }

        send(0);
        send(1);
        send(2);
        send(3);
    }
}



void SEQ_Mod_ReceiveButtonEvents() {
    u8 board = 0;
    while (board < MIOS32_IIC_IO_BOARDS) {
        s32 error = MIOS32_IIC_TransferBegin(MIOS32_IIC_IO_PORT, IIC_Non_Blocking);
        DEBUG_MSG("error: %d\n", error);
        if (error) continue;

        u8 _buffer[4] = {0, 0, 0, 0};
        error = MIOS32_IIC_Transfer(MIOS32_IIC_IO_PORT, IIC_Read, (MIOS32_IIC_IO_BASE_ADDRESS + board) << 1U, &_buffer[0], 1);
        if (!error)
            error = MIOS32_IIC_TransferWait(MIOS32_IIC_IO_PORT);

        MIOS32_IIC_TransferFinished(MIOS32_IIC_IO_PORT);

/*
        if (!error) {
            if (_buffer[0]) {
                handleEvent(board, _buffer[0]);
            }
        }
*/

        ++board;
    }
}


s32 SEQ_Mod_Idle(void)
{
//    if (i2c_writing_enabled) {
//        SEQ_Mod_SendLedValues();
//    }
    if (i2c_reading_enabled) {
        SEQ_Mod_ReceiveButtonEvents();
    }
    return 0;
}


void readAndHandle(void (*out)(char *format, ...), u8 i2cAddress, u8 board) {
    out("Reading a byte from I2C\n");
    u8 event = 0;
    s32 error = MIOS32_IIC_Transfer(MIOS32_IIC_IO_PORT, IIC_Read, (i2cAddress + board) << 1U, &event, 1);
    out("Status: %d\n", error);
    if (!error) {
        error = MIOS32_IIC_TransferWait(MIOS32_IIC_IO_PORT);
        out("Status: %d\n", error);
        MIOS32_IIC_TransferFinished(MIOS32_IIC_IO_PORT);
        if (!error) {
            out("Result: %d\n", event);
            if (event) {
                handleEvent(board, event);
            }
        }
    }
}

void readAndHandleNB(void (*out)(char *format, ...), u8 i2cAddress, u8 board) {
    out("Reading a byte from I2C\n");
    s32 error = MIOS32_IIC_TransferBegin(MIOS32_IIC_IO_PORT, IIC_Non_Blocking);
    out("Status: %d\n", error);
    if (error) return;

    u8 _buffer[4] = {0, 0, 0, 0};
    error = MIOS32_IIC_Transfer(MIOS32_IIC_IO_PORT, IIC_Read, (MIOS32_IIC_IO_BASE_ADDRESS + board) << 1U, &_buffer[0], 1);
    out("Status: %d\n", error);
    if (!error)
        error = MIOS32_IIC_TransferWait(MIOS32_IIC_IO_PORT);
    out("Status: %d\n", error);

    MIOS32_IIC_TransferFinished(MIOS32_IIC_IO_PORT);

    if (!error) {
        if (_buffer[0]) {
            out("EVENT %d\n", _buffer[0]);
            handleEvent(board, _buffer[0]);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// Parser for a complete line
// Returns > 0 if command line matches with one of supported terminal commands
/////////////////////////////////////////////////////////////////////////////
s32 SEQ_Mod_TerminalParseLine(char *input, void *_output_function)
{
    void (*out)(char *format, ...) = _output_function;
    char *separators = " \t";
    char *brkt;
    char *parameter;

    // since strtok_r works destructive (separators in *input replaced by NUL), we have to restore them
    // on an unsuccessful call (whenever this function returns < 1)
    int input_len = strlen(input);

    if ((parameter = strtok_r(input, separators, &brkt))) {
        if (strcasecmp(parameter, "mod_read_i2c") == 0) {
            readAndHandleNB(out, MIOS32_IIC_IO_BASE_ADDRESS, 0);
            readAndHandleNB(out, MIOS32_IIC_IO_BASE_ADDRESS, 1);
            readAndHandleNB(out, MIOS32_IIC_IO_BASE_ADDRESS, 2);
            readAndHandleNB(out, MIOS32_IIC_IO_BASE_ADDRESS, 3);
            return 1; // command taken
        }
        else if (strcasecmp(parameter, "mod_read_i2c_on") == 0) {
            out("Switching on reading from I2C\n");
            i2c_reading_enabled = 1;
            return 1; // command taken
        }
        else if (strcasecmp(parameter, "mod_read_i2c_off") == 0) {
            out("Switching off reading from I2C\n");
            i2c_reading_enabled = 0;
            return 1; // command taken
        }
        else if (strcasecmp(parameter, "mod_tran_on") == 0) {
            out("Switching on transposing\n");
            transpose_enabled = 1;
            return 1; // command taken
        }
        else if (strcasecmp(parameter, "mod_tran_on") == 0) {
            out("Switching off transposing\n");
            transpose_enabled = 0;
            return 1; // command taken
        }
    }

    // restore input line (replace NUL characters by spaces)
    int i;
    char *input_ptr = input;
    for(i=0; i<input_len; ++i, ++input_ptr)
        if( !*input_ptr )
            *input_ptr = ' ';

    return 0; // command not taken
}


/////////////////////////////////////////////////////////////////////////////
// Function to initialize SEQ Modifications
/////////////////////////////////////////////////////////////////////////////
s32 SEQ_Mod_Init(u32 mode)
{
    for (int i = 0; i < SEQ_HWCFG_NUM_ENCODERS; i++) {
        encoder_value[i] = 0;
        encoder_reported_value[i] = 0;
    }
    
    MIOS32_IIC_Init(0);

    xTaskCreate(
            TASK_CommunicateWithHIDBoards,
            (const portCHAR *) "ScanHIDBoards",
            configMINIMAL_STACK_SIZE,
            NULL,
            PRIORITY_TASK_SCAN_HID_BOARDS,
            NULL
    );

    return 0;
}


#endif /* SEQ_USE_MOD */
