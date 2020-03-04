// $Id$
/*
 * The command/configuration Terminal
 *
 * ==========================================================================
 *
 *  Copyright (C) 2010 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

/////////////////////////////////////////////////////////////////////////////
// Include files
/////////////////////////////////////////////////////////////////////////////

#include <mios32.h>
#include <string.h>

#include "app.h"
#include "terminal.h"
#include "i2c_comm.h"

/////////////////////////////////////////////////////////////////////////////
// Local defines
/////////////////////////////////////////////////////////////////////////////

#define STRING_MAX 80


/////////////////////////////////////////////////////////////////////////////
// Local variables
/////////////////////////////////////////////////////////////////////////////

static char line_buffer[STRING_MAX];
static u16 line_ix;


/////////////////////////////////////////////////////////////////////////////
// Local prototypes
/////////////////////////////////////////////////////////////////////////////

static s32 TERMINAL_PrintSystem(void *_output_function);

static s32 TERMINAL_PrintIPs(void *_output_function);


/////////////////////////////////////////////////////////////////////////////
// Initialisation
/////////////////////////////////////////////////////////////////////////////
s32 TERMINAL_Init(u32 mode) {
    // install the callback function which is called on incoming characters
    // from MIOS Terminal
    MIOS32_MIDI_DebugCommandCallback_Init(TERMINAL_Parse);

    // clear line buffer
    line_buffer[0] = 0;
    line_ix = 0;

    return 0; // no error
}


/////////////////////////////////////////////////////////////////////////////
// help function which parses a decimal or hex value
// returns >= 0 if value is valid
// returns -1 if value is invalid
/////////////////////////////////////////////////////////////////////////////
static s32 get_dec(char *word) {
    if (word == NULL)
        return -1;

    char *next;
    long l = strtol(word, &next, 0);

    if (word == next)
        return -1;

    return l; // value is valid
}


/////////////////////////////////////////////////////////////////////////////
// help function which parses for on or off
// returns 0 if 'off', 1 if 'on', -1 if invalid
/////////////////////////////////////////////////////////////////////////////
static s32 get_on_off(char *word) {
    if (strcmp(word, "on") == 0)
        return 1;

    if (strcmp(word, "off") == 0)
        return 0;

    return -1;
}


/////////////////////////////////////////////////////////////////////////////
// Parser
/////////////////////////////////////////////////////////////////////////////
s32 TERMINAL_Parse(mios32_midi_port_t port, u8 byte) {
    // temporary change debug port (will be restored at the end of this function)
    mios32_midi_port_t prev_debug_port = MIOS32_MIDI_DebugPortGet();
    MIOS32_MIDI_DebugPortSet(port);

    if (byte == '\r') {
        // ignore
    } else if (byte == '\n') {
        //MUTEX_MIDIOUT_TAKE;
        TERMINAL_ParseLine(line_buffer, MIOS32_MIDI_SendDebugMessage);
        //MUTEX_MIDIOUT_GIVE;
        line_ix = 0;
        line_buffer[line_ix] = 0;
    } else if (line_ix < (STRING_MAX - 1)) {
        line_buffer[line_ix++] = byte;
        line_buffer[line_ix] = 0;
    }

    // restore debug port
    MIOS32_MIDI_DebugPortSet(prev_debug_port);

    return 0; // no error
}


/////////////////////////////////////////////////////////////////////////////
// Parser for a complete line - also used by shell.c for telnet
/////////////////////////////////////////////////////////////////////////////
s32 TERMINAL_ParseLine(char *input, void *_output_function) {
    void (*out)(char *format, ...) = _output_function;
    char *separators = " \t";
    char *brkt;
    char *parameter;

    if ((parameter = strtok_r(input, separators, &brkt))) {
        if (strcmp(parameter, "help") == 0) {
            out("Following commands are available:");
            out("  send");
        } else if (strcmp(parameter, "sr1") == 0) {
            uint16_t sr1 = I2C_ReadRegister(I2C1, I2C_Register_SR1);
            MIOS32_MIDI_SendDebugMessage("SR1: %04x!\n", sr1);
        } else if (strcmp(parameter, "sr2") == 0) {
            uint16_t sr2 = I2C_ReadRegister(I2C1, I2C_Register_SR2);
            MIOS32_MIDI_SendDebugMessage("SR2: %04x!\n", sr2);
        } else if (strcmp(parameter, "check") == 0) {
            u32 status;
            if((status=MIOS32_IIC_TransferCheck(1)) < 0)
                MIOS32_MIDI_SendDebugMessage("MIOS32_IIC_TransferCheck failed with %d!\n", status);
        } else if (strcmp(parameter, "wait") == 0) {
            u32 status;
            if((status=MIOS32_IIC_TransferWait(1)) < 0)
                MIOS32_MIDI_SendDebugMessage("MIOS32_IIC_TransferWait failed with %d!\n", status);
        } else if (strcmp(parameter, "send") == 0) {
            I2C_Comm_Send(0);
        } else {
            out("Unknown command - type 'help' to list available commands!");
        }
    }

    return 0; // no error
}
