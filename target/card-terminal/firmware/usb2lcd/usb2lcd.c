/*
 Based on LUFA example SerialToLCD

             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2012  Simon Foster (simon.foster [at] inbox [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file 
 *
 *  Main source file for the SerialToLCD program. This file contains the main tasks of
 *  the project and is responsible for the initial application hardware configuration.
 */

#include "usb2lcd.h"
#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.h"
#include "cpu/avr/drivers/display/mt12232/terminal.h"
#include <util/delay.h>
#include <avr/io.h>



/** Circular buffer to hold data from the host before it is sent to the LCD */
static RingBuffer_t FromHost_Buffer;

/** Underlying data buffer for \ref FromHost_Buffer, where the stored bytes are located. */
static uint8_t      FromHost_Buffer_Data[128];

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
	{
		.Config =
			{
				.ControlInterfaceNumber   = 0,
				.DataINEndpoint           =
					{
						.Address          = CDC_TX_EPADDR,
						.Size             = CDC_TXRX_EPSIZE,
						.Banks            = 1,
					},
				.DataOUTEndpoint =
					{
						.Address          = CDC_RX_EPADDR,
						.Size             = CDC_TXRX_EPSIZE,
						.Banks            = 1,
					},
				.NotificationEndpoint =
					{
						.Address          = CDC_NOTIFICATION_EPADDR,
						.Size             = CDC_NOTIFICATION_EPSIZE,
						.Banks            = 1,
					},
			},
	};


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	RingBuffer_InitBuffer(&FromHost_Buffer, FromHost_Buffer_Data, sizeof(FromHost_Buffer_Data));

	GlobalInterruptEnable();

	for (;;)
	{
		/* Only try to read in bytes from the CDC interface if the transmit buffer is not full */
		if (!(RingBuffer_IsFull(&FromHost_Buffer)))
		{
			int16_t ReceivedByte = CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);

			/* Read bytes from the USB OUT endpoint into the USART transmit buffer */
			if (!(ReceivedByte < 0))
			  RingBuffer_Insert(&FromHost_Buffer, ReceivedByte);
		}

		while (RingBuffer_GetCount(&FromHost_Buffer) > 0)
		{
			int16_t byte = RingBuffer_Remove(&FromHost_Buffer);
                        terminal__putc(byte == '\r' ? '\n' : byte);
			
		}

		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the application's functionality. */
void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Hardware Initialization */
	USB_Init();

	/* Power up display */
        // backlight
        DDRD |= (1<<0);
        PORTD |= (1<<0);

        LCDG_InitPort();
        _delay_ms(30);
        LCDG_InitLcd();
        LCDG_ClrAllDisp();
	
	/* Start the flush timer so that overflows occur rapidly to push received bytes to the USB interface */
	TCCR0B = (1 << CS02);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
}

void EVENT_USB_Device_StartOfFrame(void) {
}

void EVENT_USB_Device_Reset(void) {
}
