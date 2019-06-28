/*
 * Based on MIDIbox SEQ MIDI Terminal, by Thorsten Klose (tk@midibox.org)
 */

/////////////////////////////////////////////////////////////////////////////
// Include files
/////////////////////////////////////////////////////////////////////////////

#include <mios32.h>
#include <string.h>

#include <app_lcd.h>

#include "app.h"
#include "seq_terminal.h"

extern void vPortMallocDebugInfo(void);


/////////////////////////////////////////////////////////////////////////////
// Local defines
/////////////////////////////////////////////////////////////////////////////

#define STRING_MAX 100 // recommended size for file transfers via FILE_BrowserHandler()


/////////////////////////////////////////////////////////////////////////////
// Local variables
/////////////////////////////////////////////////////////////////////////////

static char line_buffer[STRING_MAX];
static u16 line_ix;

/////////////////////////////////////////////////////////////////////////////
// Local prototypes
/////////////////////////////////////////////////////////////////////////////

static s32 TERMINAL_ParseFilebrowser(mios32_midi_port_t port, char byte);

//static s32 TERMINAL_BrowserUploadCallback(char *filename);


/////////////////////////////////////////////////////////////////////////////
// Initialisation
/////////////////////////////////////////////////////////////////////////////
s32 SEQ_TERMINAL_Init(u32 mode) {
    // install the callback function which is called on incoming characters from MIOS Terminal
    MIOS32_MIDI_DebugCommandCallback_Init(SEQ_TERMINAL_Parse);

    // install the callback function which is called on incoming characters from MIOS Filebrowser
//  MIOS32_MIDI_FilebrowserCommandCallback_Init(TERMINAL_ParseFilebrowser);

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
// Parser
/////////////////////////////////////////////////////////////////////////////
s32 SEQ_TERMINAL_Parse(mios32_midi_port_t port, char byte) {
    // temporary change debug port (will be restored at the end of this function)
    mios32_midi_port_t prev_debug_port = MIOS32_MIDI_DebugPortGet();
    MIOS32_MIDI_DebugPortSet(port);

    if (byte == '\r') {
        // ignore
    } else if (byte == '\n') {
        SEQ_TERMINAL_ParseLine(line_buffer, APP_SendDebugMessage);
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
s32 SEQ_TERMINAL_ParseLine(char *input, void *_output_function) {
    void (*out)(char *format, ...) = _output_function;
    char *separators = " \t";
    char *brkt;
    char *parameter;

//  MUTEX_MIDIOUT_TAKE;


    if (APP_LCD_TerminalParseLine(input, _output_function) >= 1)
        return 0; // command parsed


//  MUTEX_MIDIOUT_GIVE;

    if ((parameter = strtok_r(line_buffer, separators, &brkt))) {
        if (strcmp(parameter, "help") == 0) {
            SEQ_TERMINAL_PrintHelp(out);
        } else if (strcmp(parameter, "system") == 0) {
            SEQ_TERMINAL_PrintSystem(out);
        } else if (strcmp(parameter, "memory") == 0) {
            // new: expert option (therefore not documented in help page):
            // "memory <from-address> <to-address> dumps any memory region (not protected against bus errors - potential hard fault!)
            char *arg;
            if ((arg = strtok_r(NULL, separators, &brkt))) {
                int begin_addr = get_dec(arg);
                int end_addr = -1;

                if ((arg = strtok_r(NULL, separators, &brkt))) {
                    end_addr = get_dec(arg);
                }

                if (begin_addr == -1 || end_addr == -1) {
                    out("SYNTAX: memory <begin-addr> <end-addr>");
                } else if (begin_addr > end_addr) {
                    out("ERROR: end address has to be greater equal the start address");
                } else {
                    u32 size = end_addr - begin_addr;
                    if (size > 0x10000) {
                        out("ERROR: it isn't recommended to dump more than 64k at once!");
                    } else {
                        u8 *ptr = (u8 *) begin_addr;
                        MIOS32_MIDI_SendDebugHexDump(ptr, size);
                    }
                }
            } else {
                SEQ_TERMINAL_PrintMemoryInfo(out);
            }
        } else if (strcmp(parameter, "global") == 0) {
            SEQ_TERMINAL_PrintGlobalConfig(out);
        } else if (strcmp(parameter, "reset") == 0) {
            MIOS32_SYS_Reset();
        } else {
            out("Unknown command - type 'help' to list available commands!");
        }
    }

    return 0; // no error
}


s32 SEQ_TERMINAL_PrintHelp(void *_output_function) {
    void (*out)(char *format, ...) = _output_function;

    out("Welcome to " MIOS32_LCD_BOOT_MSG_LINE1 "!");
    out("Following commands are available:");
    out("  system:         print system info");
    out("  memory:         print memory allocation info");
    out("  sdcard:         print SD Card info");
    out("  sdcard_format:  formats the SD Card (you will be asked for confirmation)");
    out("  global:         print global configuration");
    out("  config:         print local session configuration");
    out("  tracks:         print overview of all tracks");
    out("  track <track>:  print info about a specific track");
    out("  mixer:          print current mixer map");
    out("  song:           print current song info");
    out("  grooves:        print groove templates");
    out("  bookmarks:      print bookmarks");
    out("  router:         print MIDI router info");
    out("  tpd <string>:   print a scrolled text on the TPD");
#ifndef MBSEQV4L
    out("  lcd <string>:   print a message on LCD");
#endif
    out("  reset:          resets the MIDIbox SEQ (!)");
    out("  help:           this page");

    return 0; // no error
}


s32 SEQ_TERMINAL_PrintSystem(void *_output_function) {
    void (*out)(char *format, ...) = _output_function;
    char str_buffer[128];

    out("System Informations:");
    out("====================");
    out(MIOS32_LCD_BOOT_MSG_LINE1 " " MIOS32_LCD_BOOT_MSG_LINE2 "");

    mios32_sys_time_t t = MIOS32_SYS_TimeGet();
    int hours = (t.seconds / 3600) % 24;
    int minutes = (t.seconds % 3600) / 60;
    int seconds = (t.seconds % 3600) % 60;

    out("Operating System: MIOS32");
    out("Board: " MIOS32_BOARD_STR "");
    out("Chip Family: " MIOS32_FAMILY_STR "");
    if (MIOS32_SYS_SerialNumberGet((char *) str_buffer) >= 0)
        out("Serial Number: %s\n", str_buffer);
    else
        out("Serial Number: ?");
    out("Flash Memory Size: %d bytes\n", MIOS32_SYS_FlashSizeGet());
    out("RAM Size: %d bytes\n", MIOS32_SYS_RAMSizeGet());


    out("Systime: %02d:%02d:%02d\n", hours, minutes, seconds);

#if !defined(MIOS32_FAMILY_EMULATION) && (configGENERATE_RUN_TIME_STATS || configUSE_TRACE_FACILITY)
    // send Run Time Stats to MIOS terminal
    out("FreeRTOS Task RunTime Stats:");
    FREERTOS_UTILS_RunTimeStats();
#endif

    out("done.");

    return 0; // no error
}


s32 SEQ_TERMINAL_PrintGlobalConfig(void *_output_function) {
    void (*out)(char *format, ...) = _output_function;

    out("Global Configuration:");
    out("=====================");

    out("done.");

    return 0; // no error
}

s32 SEQ_TERMINAL_PrintMemoryInfo(void *_output_function) {
#if defined(MIOS32_FAMILY_EMULATION)
    void (*out)(char *format, ...) = _output_function;
    out("Not supported in emulation!");
#else
//  MUTEX_MIDIOUT_TAKE;
    vPortMallocDebugInfo();
//  MUTEX_MIDIOUT_GIVE;
#endif

    return 0; // no error
}

