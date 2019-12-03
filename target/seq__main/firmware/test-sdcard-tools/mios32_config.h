#ifndef _MIOS32_CONFIG_H
#define _MIOS32_CONFIG_H


#define MIOS32_DONT_USE_AIN
#define MIOS32_DONT_USE_DIN
#define MIOS32_DONT_USE_DOUT
#define MIOS32_DONT_USE_ENC
#define MIOS32_DONT_USE_SRIO
#define MIOS32_DONT_USE_UART
#define MIOS32_DONT_USE_ENC28J60
#define MIOS32_DONT_USE_SPI1
#define MIOS32_DONT_USE_SPI2
#define MIOS32_DONT_USE_OSC
#define MIOS32_DONT_USE_MF
#define MIOS32_DONT_USE_IIC_BS
#define MIOS32_DONT_USE_IIC_MIDI
#define MIOS32_DONT_USE_UART_MIDI

#define MIOS32_CLCD_PARALLEL_DISPLAYS 1
#define MIOS32_CLCD_PARALLEL_LCD0_RS_PORT GPIOC
#define MIOS32_CLCD_PARALLEL_LCD0_RS_PIN GPIO_Pin_1
#define MIOS32_CLCD_PARALLEL_LCD0_RW_PORT GPIOC
#define MIOS32_CLCD_PARALLEL_LCD0_RW_PIN GPIO_Pin_2
#define MIOS32_CLCD_PARALLEL_LCD0_E_PORT GPIOC
#define MIOS32_CLCD_PARALLEL_LCD0_E_PIN GPIO_Pin_3
#define MIOS32_CLCD_PARALLEL_LCD0_DATA_PORT GPIOE
#define MIOS32_CLCD_PARALLEL_LCD0_DATA_PINS_OFFSET 8U


// The boot message which is print during startup and returned on a SysEx query
#define MIOS32_LCD_BOOT_MSG_LINE1 "SD Card Tools"
#define MIOS32_LCD_BOOT_MSG_LINE2 "(C) 2010 T.Klose and P.Taylor"

// FatFs configuration: support long filenames
#define FATFS_USE_LFN 1
#define FATFS_MAX_LFN 255

#define MIOS32_DONT_USE_SPI1
#define MIOS32_DONT_USE_SPI2


#endif /* _MIOS32_CONFIG_H */
