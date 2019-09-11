/*
 * Local MIOS32 configuration file
 *
 * this file allows to disable (or re-configure) default functions of MIOS32
 * available switches are listed in $MIOS32_PATH/modules/mios32/MIOS32_CONFIG.txt
 *
 */

#ifndef _MIOS32_CONFIG_H
#define _MIOS32_CONFIG_H

//#define MIOS32_DONT_USE_BOARD
#define MIOS32_LCD_BOOT_MSG_DELAY 0

#define MIOS32_DONT_USE_AIN
#define MIOS32_DONT_USE_DIN
#define MIOS32_DONT_USE_DOUT
#define MIOS32_DONT_USE_ENC
#define MIOS32_DONT_USE_LCD
#define MIOS32_DONT_USE_SRIO
#define MIOS32_DONT_USE_UART
#define MIOS32_DONT_USE_SDCARD
#define MIOS32_DONT_USE_ENC28J60
#define MIOS32_DONT_USE_SPI
#define MIOS32_DONT_USE_SPI0
#define MIOS32_DONT_USE_SPI1
#define MIOS32_DONT_USE_SPI2
#define MIOS32_DONT_USE_OSC
#define MIOS32_DONT_USE_MF
#define MIOS32_DONT_USE_IIC_BS
#define MIOS32_DONT_USE_IIC_MIDI
#define MIOS32_DONT_USE_UART_MIDI


#define MIOS32_USB_PRODUCT_STR  "test-hd44780-4wire"

#define MIOS32_IIC0_BUS_FREQUENCY 100000

#endif /* _MIOS32_CONFIG_H */
