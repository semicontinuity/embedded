/**
 * Defines for your entire project at one place
 * 
 * @author     Tilen Majerle
 * @email      tilen@majerle.eu
 * @website    http://stm32f4-discovery.net
 * @version    v1.0
 * @ide        Keil uVision 5
 * @license    GNU GPL v3
 *	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2015
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#ifndef TM_DEFINES_H
#define TM_DEFINES_H

//#include "stm32fxxx_hal.h"

//#include <stdint.h>
//typedef uint8_t u8;

#define MIOS32_CLCD_PARALLEL_DISPLAYS 4

#define MIOS32_CLCD_PARALLEL_LCD0_RS_PORT GPIOD
#define MIOS32_CLCD_PARALLEL_LCD0_RS_PIN GPIO_Pin_4
#define MIOS32_CLCD_PARALLEL_LCD0_RW_PORT GPIOD
#define MIOS32_CLCD_PARALLEL_LCD0_RW_PIN GPIO_Pin_7
#define MIOS32_CLCD_PARALLEL_LCD0_E_PORT GPIOD
#define MIOS32_CLCD_PARALLEL_LCD0_E_PIN GPIO_Pin_3
#define MIOS32_CLCD_PARALLEL_LCD0_DATA_PORT GPIOD
#define MIOS32_CLCD_PARALLEL_LCD0_DATA_PINS_OFFSET 8U

#define MIOS32_CLCD_PARALLEL_LCD1_RS_PORT GPIOA
#define MIOS32_CLCD_PARALLEL_LCD1_RS_PIN GPIO_Pin_13
#define MIOS32_CLCD_PARALLEL_LCD1_RW_PORT GPIOA
#define MIOS32_CLCD_PARALLEL_LCD1_RW_PIN GPIO_Pin_14
#define MIOS32_CLCD_PARALLEL_LCD1_E_PORT GPIOA
#define MIOS32_CLCD_PARALLEL_LCD1_E_PIN GPIO_Pin_15
#define MIOS32_CLCD_PARALLEL_LCD1_DATA_PORT GPIOB
#define MIOS32_CLCD_PARALLEL_LCD1_DATA_PINS_OFFSET 0U

#define MIOS32_CLCD_PARALLEL_LCD2_RS_PORT GPIOC
#define MIOS32_CLCD_PARALLEL_LCD2_RS_PIN GPIO_Pin_0
#define MIOS32_CLCD_PARALLEL_LCD2_RW_PORT GPIOC
#define MIOS32_CLCD_PARALLEL_LCD2_RW_PIN GPIO_Pin_2
#define MIOS32_CLCD_PARALLEL_LCD2_E_PORT GPIOC
#define MIOS32_CLCD_PARALLEL_LCD2_E_PIN GPIO_Pin_3
#define MIOS32_CLCD_PARALLEL_LCD2_DATA_PORT GPIOE
#define MIOS32_CLCD_PARALLEL_LCD2_DATA_PINS_OFFSET 0U

#define MIOS32_CLCD_PARALLEL_LCD3_RS_PORT GPIOC
#define MIOS32_CLCD_PARALLEL_LCD3_RS_PIN GPIO_Pin_13
#define MIOS32_CLCD_PARALLEL_LCD3_RW_PORT GPIOA
#define MIOS32_CLCD_PARALLEL_LCD3_RW_PIN GPIO_Pin_3
#define MIOS32_CLCD_PARALLEL_LCD3_E_PORT GPIOA
#define MIOS32_CLCD_PARALLEL_LCD3_E_PIN GPIO_Pin_6
#define MIOS32_CLCD_PARALLEL_LCD3_DATA_PORT GPIOE
#define MIOS32_CLCD_PARALLEL_LCD3_DATA_PINS_OFFSET 8U

/* Put your global defines for all libraries here used in your project */

/* Defines for RCC settings for system */
/* I've added these defines in options for target in Keil uVision for each target different settings */
//#define RCC_OSCILLATORTYPE    RCC_OSCILLATORTYPE_HSE /*!< Used to select system oscillator type */
//#define RCC_PLLM              8                      /*!< Used for PLL M parameter */
//#define RCC_PLLN              360                    /*!< Used for PLL N parameter */
//#define RCC_PLLP              2                      /*!< Used for PLL P parameter */
//#define RCC_PLLQ              7                      /*!< Used for PLL Q parameter */
//#define RCC_PLLR              10                     /*!< Used for PLL R parameter, available on STM32F446xx */


#endif
