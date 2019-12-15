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

// V4+ switch depends on used processor
#if defined(MIOS32_FAMILY_STM32F4xx)
# define MBSEQV4P
#endif

//#define MIOS32_DONT_USE_AIN
//#define MIOS32_DONT_USE_UART
//#define MIOS32_DONT_USE_SPI1
//#define MIOS32_DONT_USE_SPI2
//#define MIOS32_DONT_USE_MF
//#define MIOS32_DONT_USE_IIC_BS
//#define MIOS32_DONT_USE_UART_MIDI

//#define MIOS32_DONT_USE_DIN
//#define MIOS32_DONT_USE_DOUT
//#define MIOS32_DONT_USE_ENC
//#define MIOS32_DONT_USE_SRIO
//#define MIOS32_DONT_USE_ENC28J60
//#define MIOS32_DONT_USE_OSC
//#define MIOS32_DONT_USE_IIC_MIDI


#define MIOS32_CLCD_PARALLEL_DISPLAYS 2

#define MIOS32_CLCD_PARALLEL_LCD0_RS_PORT GPIOC
#define MIOS32_CLCD_PARALLEL_LCD0_RS_PIN GPIO_Pin_1
#define MIOS32_CLCD_PARALLEL_LCD0_RW_PORT GPIOC
#define MIOS32_CLCD_PARALLEL_LCD0_RW_PIN GPIO_Pin_13
#define MIOS32_CLCD_PARALLEL_LCD0_E_PORT GPIOC
#define MIOS32_CLCD_PARALLEL_LCD0_E_PIN GPIO_Pin_2
#define MIOS32_CLCD_PARALLEL_LCD0_DATA_PORT GPIOE
#define MIOS32_CLCD_PARALLEL_LCD0_DATA_PINS_OFFSET 8U

#define MIOS32_CLCD_PARALLEL_LCD1_RS_PORT GPIOC
#define MIOS32_CLCD_PARALLEL_LCD1_RS_PIN GPIO_Pin_1
#define MIOS32_CLCD_PARALLEL_LCD1_RW_PORT GPIOC
#define MIOS32_CLCD_PARALLEL_LCD1_RW_PIN GPIO_Pin_13
#define MIOS32_CLCD_PARALLEL_LCD1_E_PORT GPIOC
#define MIOS32_CLCD_PARALLEL_LCD1_E_PIN GPIO_Pin_2
#define MIOS32_CLCD_PARALLEL_LCD1_DATA_PORT GPIOE
#define MIOS32_CLCD_PARALLEL_LCD1_DATA_PINS_OFFSET 8U



// The boot message which is print during startup and returned on a SysEx query
#define MIOS32_LCD_BOOT_MSG_DELAY 0 // we delay the boot and print a message inside the app
//                                <---------------------->
#ifdef MBSEQV4P
#define MIOS32_LCD_BOOT_MSG_LINE1 "DevOps controller"
#else
#define MIOS32_LCD_BOOT_MSG_LINE1 "MIDIbox SEQ V4.096"
#endif
#define MIOS32_LCD_BOOT_MSG_LINE2 "================="

// USB settings
#ifdef MBSEQV4P
# define MIOS32_USB_PRODUCT_STR  "MIDIbox SEQ V4+"
#else
# define MIOS32_USB_PRODUCT_STR  "MIDIbox SEQ V4"
#endif
#define MIOS32_USB_MIDI_NUM_PORTS 4

// port used for debugging via MIDI
//#define MIOS32_MIDI_DEBUG_PORT USB0

// function used to output debug messages (must be printf compatible!)
extern void APP_SendDebugMessage(char *format, ...);
#define DEBUG_MSG APP_SendDebugMessage

#endif /* _MIOS32_CONFIG_H */
