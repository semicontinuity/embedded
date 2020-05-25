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

/* Put your global defines for all libraries here used in your project */

/* Defines for RCC settings for system */
/* I've added these defines in options for target in Keil uVision for each target different settings */
//#define RCC_OSCILLATORTYPE    RCC_OSCILLATORTYPE_HSE /*!< Used to select system oscillator type */
//#define RCC_PLLM              8                      /*!< Used for PLL M parameter */
//#define RCC_PLLN              360                    /*!< Used for PLL N parameter */
//#define RCC_PLLP              2                      /*!< Used for PLL P parameter */
//#define RCC_PLLQ              7                      /*!< Used for PLL Q parameter */
//#define RCC_PLLR              10                     /*!< Used for PLL R parameter, available on STM32F446xx */

#define SSD1306_I2C              I2C1
#define SSD1306_I2C_PINSPACK     TM_I2C_PinsPack_2

//Select custom I2C address.
#define SSD1306_I2C_ADDR         0x78

//Select custom width and height if your LCD differs in size
#define SSD1306_WIDTH            128
#define SSD1306_HEIGHT           64

#endif
