// =============================================================================
// 1-wire thermometer
// The bus is implemented using USART + external 2xFET circuit.
//
// Does not work, because FET master circuit is not fast enough.
// =============================================================================


#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.h"
#include "cpu/avr/drivers/display/mt12232/terminal.h"

#include "OWIPolled.h"
#include "OWIHighLevelFunctions.h"
#include "OWIBitFunctions.h"
#include "common_files/OWIcrc.h"

#include "util/hex.h"
#include <stdint.h>

const char MSG_INITIALIZING[]    PROGMEM = "Initializing 1-wire\n";
const char MSG_DETECTING[]    PROGMEM = "Detecting device(s)\n";
const char MSG_DEVICES_PRESENT[] PROGMEM = "Device(s) present\n";
const char MSG_ERROR[] PROGMEM = "Error\n";


#define DS18X20_READ (0xBE)
#define DS18X20_OK          0x00
#define DS18X20_ERROR       0x01
#define DS18X20_START_FAIL  0x02
#define DS18X20_ERROR_CRC   0x03

#define DS18X20_CONVERT_T   0x44
#define DS18X20_SP_SIZE  9


void terminal__print_hex(const uint8_t value) {
    const uint16_t string = byte__to_hex_string(value);
    const uint8_t h = string >> 8;
    const uint8_t l = string & 0xFF;
    terminal__putc(h);
    terminal__putc(l);
}


void terminal__print_scratchpad(uint8_t* scratchpad) {
    uint8_t i;
    for (i = 0; i < DS18X20_SP_SIZE; i++) terminal__print_hex(scratchpad[i]);
}


uint8_t DS18X20_convert_t(void) {
    OWI_SendByte(DS18X20_CONVERT_T, 0);
    return 0;
}


uint8_t DS18X20_read_scratchpad(uint8_t* scratchpad) {
    uint8_t i;
    OWI_SendByte(DS18X20_READ, 0);
    for (i = 0; i < DS18X20_SP_SIZE; i++) scratchpad[i] = OWI_ReceiveByte(0);

    return OWI_CheckScratchPadCRC(scratchpad);
}


uint8_t scratchpad[DS18X20_SP_SIZE];


int main(int argc, char **argv) {
    MCUSR &= ~_BV(WDRF);
    wdt_disable();

    // clock prescaler 1
    CLKPR = 0x80;
    CLKPR = 0x00;

    // backlight ON
    DDRD |= (1<<0);
    PORTD |= (1<<0);

    // RTS=0
    DDRD |= (1<<6);
    PORTD &= ~(1<<6);


    LCDG_InitPort();
    _delay_ms(30);  // takes longer?
    LCDG_InitLcd();
    LCDG_ClrAllDisp();

    terminal__init();
    terminal__print_P(MSG_INITIALIZING);
    OWI_Init();

    terminal__print_P(MSG_DETECTING);
    if (OWI_DetectPresence())
        terminal__print_P(MSG_DEVICES_PRESENT);
    else
        terminal__print_P(PSTR("No devices present\n"));
    OWI_SkipRom(0);
    terminal__putc('.');

    DS18X20_convert_t();
    terminal__putc('.');
    _delay_ms(750);  // takes longer?    
    terminal__putc('.');
    if (DS18X20_read_scratchpad(scratchpad)) terminal__print_P(MSG_ERROR);
    terminal__putc('.');
    terminal__print_scratchpad(scratchpad);

    while(1);
    return 0;
}
