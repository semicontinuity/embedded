//--------------------------------------------------------------------------
/*
Program for writing to Newhaven Display 256x64 graphic OLED with SSD1322 controller (serial mode)
Original demo (c)2014 Mike LaVine - Newhaven Display International, LLC. 
Origin: http://www.newhavendisplay.com/NHD_forum/index.php/topic,64.0.html

Annotated and updated by Martin Falatic

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/
//--------------------------------------------------------------------------
//##########################################################################
//--------------------------------------------------------------------------

/*
,---------------------------------------------------------,
| Pin | Fn     | Notes                      | RPi connect |
|-----+--------+----------------------------+-------------+
|   1 | VSS    | Ground.                    | GND         |
|   2 | VBAT   | Power (3.3-5V).            | +5V         |
|   3 | NC     | Leave floating.            | -           |
|   4 | DB0    | SPI SCLK                   | SPI0_SCLK   |
|   5 | DB1    | SPI SDIN                   | SPI0_MOSI   |
|   6 | DB2    | Leave floating.            | -           |
|   7 | DB3    | -                          | GND         |
|   8 | DB4    | -                          | GND         |
|   9 | DB5    | -                          | GND         |
|  10 | DB6    | -                          | GND         |
|  11 | DB7    | -                          | GND         |
|  12 | /RD    | -                          | GND         |
|  13 | /WR    | -                          | GND         |
|  14 | /DC    | Data/Command for 4-wire.   | GPIOxx      |
|  15 | /RESET | Power Reset.               | GPIOxx      |
|  16 | /CS    | SPI Chip Select.           | SPI0_CEx_N  |
'---------------------------------------------------------'
*/


#include <SPI.h>

#define MODE_3WIRE    1   // BS1=0, BS0 = 1
#define MODE_4WIRE    2   // BS1=0, BS0 = 0, needs the RS (D/C) signal
#define MODE_SPI4W    3   // BS1=0, BS0 = 0, needs the RS (D/C) signal

#define SEND_CMD      1   // 3- and 4-wire - Display instruction (command)
#define SEND_DAT      2   // 3- and 4-wire - Display instruction (data)

#define MAXROWS      64   // Still figuring these out...
#define MAXCOLS     240   // Still figuring these out...

// Pin mappings WAVGAT UNO
#define PIN_SCLK  13
#define PIN_SDIN  11
#define PIN_CS    10                      

#define PIN_RS    9    // Register select (D/C)
#define PIN_RES   8    // Reset

#define PIN_RW    A0   // /WR (R/W) signal (can be tied low)
#define PIN_E     A1   // /RD (E) signal (can be tied low)

//int SIG_MODE = MODE_4WIRE;
//int SIG_MODE = MODE_3WIRE;
int SIG_MODE = MODE_SPI4W;

//--------------------------------------------------------------------------
//##########################################################################
//--------------------------------------------------------------------------

// This is slow. Really slow. (At 16 MHz anyway)
#define digitalPinSetVal(IOPTR, VAL) ( digitalWrite((IOPTR)->pin, VAL) )

// Much more efficient!
//#define digitalPinSetVal(IOPTR, VAL) ( (VAL == LOW) ? \
                                        (*(IOPTR)->reg &= ~(IOPTR)->mask) : \
                                        (*(IOPTR)->reg |=  (IOPTR)->mask) )
/*
struct IOMAP_Struct
{
  uint8_t pin;
  //volatile uint8_t * reg;
  //uint8_t mask;
} IOMAP_SCLK, IOMAP_SDIN, IOMAP_RS, IOMAP_RW, IOMAP_E, IOMAP_RES, IOMAP_CS;

void InitPin(struct IOMAP_Struct * IOMAP_temp, uint8_t pin)
{
  IOMAP_temp->pin  = pin;
  pinMode(pin, OUTPUT);
}
*/


struct IOMAP_Struct
{
  uint8_t pin;
  volatile uint8_t * reg;
  uint8_t mask;
} IOMAP_SCLK, IOMAP_SDIN, IOMAP_RS, IOMAP_RW, IOMAP_E, IOMAP_RES, IOMAP_CS;

void InitPin(struct IOMAP_Struct * IOMAP_temp, uint8_t pin)
{
  IOMAP_temp->pin  = pin;
  uint8_t port = digitalPinToPort(pin);
  if (port != NOT_A_PIN)
  {
    IOMAP_temp->reg  = portOutputRegister(port);
    IOMAP_temp->mask = digitalPinToBitMask(pin);
    // The following is equivalent to "pinMode(pin, OUTPUT)"
    volatile uint8_t * mode = portModeRegister(port);
    *mode |= IOMAP_temp->mask; // Output
  }
}


void InitStructsAndPins()
{
  pinMode(7, OUTPUT); digitalWrite(7, LOW);
  pinMode(6, OUTPUT); digitalWrite(6, LOW);
  pinMode(5, OUTPUT); digitalWrite(5, LOW);
  pinMode(4, OUTPUT); digitalWrite(4, LOW);
  pinMode(3, OUTPUT); digitalWrite(3, LOW);
  
  InitPin(&IOMAP_SCLK, PIN_SCLK);
  InitPin(&IOMAP_SDIN, PIN_SDIN);
  InitPin(&IOMAP_RS,   PIN_RS);
  InitPin(&IOMAP_RW,   PIN_RW);
  InitPin(&IOMAP_E,    PIN_E);
  InitPin(&IOMAP_RES,  PIN_RES);
  InitPin(&IOMAP_CS,   PIN_CS);
}

//--------------------------------------------------------------------------
//##########################################################################
//--------------------------------------------------------------------------
void displaySend(uint8_t sendType, unsigned char v)
{
  unsigned char i;

  digitalPinSetVal(&IOMAP_CS, LOW);

  if (sendType == SEND_CMD)
  { // Send a command value
    if (SIG_MODE == MODE_4WIRE || SIG_MODE == MODE_SPI4W)
    {
      digitalPinSetVal(&IOMAP_RS, LOW);
    }
    else if (SIG_MODE == MODE_3WIRE)
    {
      digitalPinSetVal(&IOMAP_SDIN, LOW);
      digitalPinSetVal(&IOMAP_SCLK, LOW);
      digitalPinSetVal(&IOMAP_SCLK, HIGH);
    }
  }
  else if (sendType == SEND_DAT)
  { // Send a data value
    if (SIG_MODE == MODE_4WIRE || SIG_MODE == MODE_SPI4W)
    {
      digitalPinSetVal(&IOMAP_RS, HIGH);
    }
    else if (SIG_MODE == MODE_3WIRE)
    {
      digitalPinSetVal(&IOMAP_SDIN, HIGH);
      digitalPinSetVal(&IOMAP_SCLK, LOW);
      digitalPinSetVal(&IOMAP_SCLK, HIGH);
    }
  }

  if (SIG_MODE == MODE_3WIRE || SIG_MODE == MODE_4WIRE)
  {
    for(i=8;i>0;i--)
    { // Decrementing is faster
      digitalPinSetVal(&IOMAP_SCLK, LOW);
      if((v&0x80)>>7==1)
      {
        digitalPinSetVal(&IOMAP_SDIN, HIGH);
      }
      else
      {
        digitalPinSetVal(&IOMAP_SDIN, LOW);
      }
      v=v<<1;
      digitalPinSetVal(&IOMAP_SCLK, HIGH);
    }
  }
  else if (SIG_MODE == MODE_SPI4W) {
    SPI.transfer(v);
  }

  digitalPinSetVal(&IOMAP_CS, HIGH);
}

//--------------------------------------------------------------------------
void Set_Column_Address(unsigned char a, unsigned char b)
{
  displaySend(SEND_CMD, 0x15); // Set Column Address
  displaySend(SEND_DAT, a);    //   Default => 0x00
  displaySend(SEND_DAT, b);    //   Default => 0x77
}

//--------------------------------------------------------------------------
void Set_Row_Address(unsigned char a, unsigned char b)
{
  displaySend(SEND_CMD, 0x75); // Set Row Address
  displaySend(SEND_DAT, a);    //   Default => 0x00
  displaySend(SEND_DAT, b);    //   Default => 0x7F
}

//--------------------------------------------------------------------------
void Set_Write_RAM()
{
  displaySend(SEND_CMD, 0x5C); // Enable MCU to Write into RAM
}

//--------------------------------------------------------------------------
void Reset_Device()
{
  // Lots of reset/tweaking commands follow
  displaySend(SEND_CMD, 0xFD); // Set Command Lock (MCU protection status)
  displaySend(SEND_DAT, 0x12); // = Reset
  
  displaySend(SEND_CMD, 0xB3); // Set Front Clock Divider / Oscillator Frequency
  displaySend(SEND_DAT, 0xD0); // = reset / 1100b 

  displaySend(SEND_CMD, 0xCA); // Set MUX Ratio
  displaySend(SEND_DAT, 0x3F); // = 63d = 64MUX

  displaySend(SEND_CMD, 0xA2); // Set Display Offset
  displaySend(SEND_DAT, 0x00); // = RESET

  displaySend(SEND_CMD, 0xA1); // Set Display Start Line
  displaySend(SEND_DAT, 0x00); // = register 00h

  displaySend(SEND_CMD, 0xA0); // Set Re-map and Dual COM Line mode
  displaySend(SEND_DAT, 0x14); // = Reset except Enable Nibble Re-map, Scan from COM[N-1] to COM0, where N is the Multiplex ratio
  displaySend(SEND_DAT, 0x11); // = Reset except Enable Dual COM mode (MUX = 63)

  displaySend(SEND_CMD, 0xB5); // Set GPIO
  displaySend(SEND_DAT, 0x00); // = GPIO0, GPIO1 = HiZ, Input Disabled

  displaySend(SEND_CMD, 0xAB); // Function Selection
  displaySend(SEND_DAT, 0x01); // = reset = Enable internal VDD regulator

  displaySend(SEND_CMD, 0xB4); // Display Enhancement A
  displaySend(SEND_DAT, 0xA0); // = Enable external VSL
  displaySend(SEND_DAT, 0xB5); // = Normal (reset)

  displaySend(SEND_CMD, 0xC1); // Set Contrast Current
  displaySend(SEND_DAT, 0x7F); // = reset

  displaySend(SEND_CMD, 0xC7); // Master Contrast Current Control
  displaySend(SEND_DAT, 0x0F); // = no change

  displaySend(SEND_CMD, 0xB9); // Select Default Linear Gray Scale table

  displaySend(SEND_CMD, 0xB1); // Set Phase Length
  displaySend(SEND_DAT, 0xE2); // = Phase 1 period (reset phase length) = 5 DCLKs, Phase 2 period (first pre-charge phase length) = 14 DCLKs

  displaySend(SEND_CMD, 0xD1); // Display Enhancement B
  displaySend(SEND_DAT, 0xA2); // = Normal (reset)
  displaySend(SEND_DAT, 0x20); // n/a

  displaySend(SEND_CMD, 0xBB); // Set Pre-charge voltage
  displaySend(SEND_DAT, 0x1F); // = 0.60 x VCC

  displaySend(SEND_CMD, 0xB6); // Set Second Precharge Period
  displaySend(SEND_DAT, 0x08); // = 8 dclks [reset]

  displaySend(SEND_CMD, 0xBE); // Set VCOMH
  displaySend(SEND_DAT, 0x07); // = 0.86 x VCC

  displaySend(SEND_CMD, 0xA6); // Set Display Mode = Normal Display

  displaySend(SEND_CMD, 0xA9); // Exit Partial Display

  displaySend(SEND_CMD, 0xAF); // Set Sleep mode OFF (Display ON)

  delay(10);
}

//--------------------------------------------------------------------------
void ClearDisplay()
{
  unsigned int i, j;
  
  // Turn off display while clearing (also hides noise at powerup)
  displaySend(SEND_CMD, 0xA4); // Set Display Mode = OFF

  Set_Column_Address(0x00,0x77);
  Set_Row_Address(0x00,0x7F);
  Set_Write_RAM();

  for(i=0;i<MAXROWS;i++)
  {
    for(j=0;j<MAXCOLS/2;j++)
    {
      displaySend(SEND_DAT, 0x00);
      displaySend(SEND_DAT, 0x00);
    }
    for(j=0;j<MAXCOLS/2;j++)
    {
      displaySend(SEND_DAT, 0x00);
      displaySend(SEND_DAT, 0x00);
    }
  }

  displaySend(SEND_CMD, 0xA6); // Set Display Mode = Normal Display
}

//--------------------------------------------------------------------------
void FillDisplay()
{
  unsigned int i, j;
  
  Set_Column_Address(0x00,0x77);
  Set_Row_Address(0x00,0x7F);
  Set_Write_RAM();

  for(i=0;i<MAXROWS;i++)
  {
    for(j=0;j<MAXCOLS/2;j++)
    {
      displaySend(SEND_DAT, 0xFF);
      displaySend(SEND_DAT, 0xFF);
    }
    for(j=0;j<MAXCOLS/2;j++)
    {
      displaySend(SEND_DAT, 0xFF);
      displaySend(SEND_DAT, 0xFF);
    }
  }
}

//--------------------------------------------------------------------------
void CheckerboardOdd()
{
  unsigned int i, j;
  
  Set_Column_Address(0x00,0x77);
  Set_Row_Address(0x00,0x7F);
  Set_Write_RAM();

  for(i=0;i<MAXROWS;i++)
  {
    for(j=0;j<MAXCOLS/2;j++)
    {
      displaySend(SEND_DAT, 0x0F);
      displaySend(SEND_DAT, 0x0F);
    }
    for(j=0;j<MAXCOLS/2;j++)
    {
      displaySend(SEND_DAT, 0xF0);
      displaySend(SEND_DAT, 0xF0);
    }
  }
}

//--------------------------------------------------------------------------
void CheckerboardEven()
{
  unsigned int i, j;
  
  Set_Column_Address(0x00,0x77);
  Set_Row_Address(0x00,0x7F);
  Set_Write_RAM();

  for(i=0;i<MAXROWS;i++)
  {
    for(j=0;j<MAXCOLS/2;j++)
    {
      displaySend(SEND_DAT, 0xF0);
      displaySend(SEND_DAT, 0xF0);
    }
    for(j=0;j<MAXCOLS/2;j++)
    {
      displaySend(SEND_DAT, 0x0F);
      displaySend(SEND_DAT, 0x0F);
    }
  }
}

//--------------------------------------------------------------------------
//##########################################################################
//--------------------------------------------------------------------------
void setup()
{
  InitStructsAndPins();
  digitalPinSetVal(&IOMAP_RS,  LOW);
  digitalPinSetVal(&IOMAP_RW,  LOW);
  digitalPinSetVal(&IOMAP_E,   LOW);
  digitalPinSetVal(&IOMAP_RES, HIGH);
  delay(1000);
  if (SIG_MODE == MODE_SPI4W) {
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    // DIV4 is almost as fast (for a 16 MHz device)
  }
  Reset_Device();
}

//--------------------------------------------------------------------------
void loop()
{ 
    //displaySend(SEND_CMD, 0xA4); // Entire Display OFF, all pixels turns OFF in GS level 0
    //displaySend(SEND_CMD, 0xA5); // Entire Display ON, all pixels turns ON in GS level 15
    ClearDisplay();
    CheckerboardOdd();
    CheckerboardEven();
    FillDisplay();
}

//--------------------------------------------------------------------------
