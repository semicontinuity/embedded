// $Id$
/*
 * Local MIOS32 configuration file
 *
 * this file allows to disable (or re-configure) default functions of MIOS32
 * available switches are listed in $MIOS32_PATH/modules/mios32/MIOS32_CONFIG.txt
 *
 */

#ifndef _MIOS32_CONFIG_H
#define _MIOS32_CONFIG_H

//#define MIOS32_DONT_USE_BOARD_LED
#define MIOS32_DONT_USE_LCD

#define MIOS32_DONT_USE_OSC
#define MIOS32_DONT_USE_AIN
#define MIOS32_DONT_USE_COM
#define MIOS32_DONT_USE_MF
#define MIOS32_DONT_USE_UART
#define MIOS32_DONT_USE_UART_MIDI
#define MIOS32_DONT_USE_IIC
#define MIOS32_DONT_USE_IIC_MIDI
#define MIOS32_DONT_USE_SPI_MIDI
#define MIOS32_DONT_USE_ENC28J60
#define MIOS32_DONT_USE_AOUT
#define MIOS32_DONT_USE_SRIO_SCAN
#define MIOS32_DONT_USE_BOARD_J5
#define MIOS32_DONT_USE_BOARD_J10
#define MIOS32_DONT_USE_BOARD_J28
#define MIOS32_DONT_USE_BOARD_J15
#define MIOS32_DONT_USE_BOARD_DAC
#define MIOS32_DONT_USE_SPI
#define MIOS32_DONT_USE_MF
#define MIOS32_DONT_USE_IIC_BS

#define MIOS32_DONT_USE_DIN

#endif /* _MIOS32_CONFIG_H */
