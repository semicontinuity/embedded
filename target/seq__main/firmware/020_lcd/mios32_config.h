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

// The boot message which is print during startup and returned on a SysEx query
#define MIOS32_LCD_BOOT_MSG_LINE1 "Tutorial #020"
#define MIOS32_LCD_BOOT_MSG_LINE2 "(C) 2009 T.Klose"


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





#endif /* _MIOS32_CONFIG_H */