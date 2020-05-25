/**
 * Keil project example for SSD1306 I2C based LCD
 *
 * Before you start, select your target, on the right of the "Load" button
 *
 * @author    Tilen Majerle
 * @email     tilen@majerle.eu
 * @website   http://stm32f4-discovery.net
 * @ide       Keil uVision 5
 * @conf      PLL parameters are set in "Options for Target" -> "C/C++" -> "Defines"
 * @packs     STM32F4xx/STM32F7xx Keil packs are requred with HAL driver support
 * @stdperiph STM32F4xx/STM32F7xx HAL drivers required
 */
/* Include core modules */
#include "stm32fxxx_hal.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32_disco.h"
#include "tm_stm32_delay.h"
#include "tm_stm32_ssd1306.h"
#include <stdint.h>

/* Write command */
#define SSD1306_WRITECOMMAND(command)      TM_I2C_Write(SSD1306_I2C, SSD1306_I2C_ADDR, 0x00, (command))

static uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

void TM_SSD1306_UpdateScreenMy(void) {
  uint8_t m;

for (m = 0; m < 8; m++) {
SSD1306_WRITECOMMAND(0xB0 + m);
SSD1306_WRITECOMMAND(0x00);
SSD1306_WRITECOMMAND(0x10);

/* Write multi data */
  TM_I2C_WriteMulti(SSD1306_I2C, SSD1306_I2C_ADDR, 0x40, &SSD1306_Buffer[SSD1306_WIDTH * m], SSD1306_WIDTH);
  }
}



void TM_SSD1306_Fill_My(void) {
  /* Set memory */
  memset(SSD1306_Buffer, 0xFF, sizeof(SSD1306_Buffer));
}


int main(void) {
	/* Init system clock for maximum system speed */
	TM_RCC_InitSystem();
	
	/* Init HAL layer */
	HAL_Init();
	
	/* Init delay */
	TM_DELAY_Init();

        TM_I2C_Init(SSD1306_I2C, SSD1306_I2C_PINSPACK, 400000);
        
        /* Check if LCD connected to I2C */
        if (TM_I2C_IsDeviceConnected(SSD1306_I2C, SSD1306_I2C_ADDR) != TM_I2C_Result_Ok) {
                /* Return false */
                return 0;
        }
        
        /* A little delay */
        Delayms(100);
        
        /* Init LCD */
        SSD1306_WRITECOMMAND(0xAE); //display off
        SSD1306_WRITECOMMAND(0x20); //Set Memory Addressing Mode...
        SSD1306_WRITECOMMAND(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
        SSD1306_WRITECOMMAND(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
        SSD1306_WRITECOMMAND(0xC8); //Set COM Output Scan Direction
        SSD1306_WRITECOMMAND(0x00); //---set low column address
        SSD1306_WRITECOMMAND(0x10); //---set high column address
        SSD1306_WRITECOMMAND(0x40); //--set start line address
        SSD1306_WRITECOMMAND(0x81); //--set contrast control register
        SSD1306_WRITECOMMAND(0xFF);
        SSD1306_WRITECOMMAND(0xA1); //--set segment re-map 0 to 127
        SSD1306_WRITECOMMAND(0xA6); //--set normal display
        SSD1306_WRITECOMMAND(0xA8); //--set multiplex ratio(1 to 64)
        SSD1306_WRITECOMMAND(0x3F); //
        SSD1306_WRITECOMMAND(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
        SSD1306_WRITECOMMAND(0xD3); //-set display offset
        SSD1306_WRITECOMMAND(0x00); //-not offset
        SSD1306_WRITECOMMAND(0xD5); //--set display clock divide ratio/oscillator frequency
        SSD1306_WRITECOMMAND(0xF0); //--set divide ratio
        SSD1306_WRITECOMMAND(0xD9); //--set pre-charge period
        SSD1306_WRITECOMMAND(0x22); //
        SSD1306_WRITECOMMAND(0xDA); //--set com pins hardware configuration
        SSD1306_WRITECOMMAND(0x12);
        SSD1306_WRITECOMMAND(0xDB); //--set vcomh
        SSD1306_WRITECOMMAND(0x20); //0x20,0.77xVcc
        SSD1306_WRITECOMMAND(0x8D); //--set DC-DC enable
        SSD1306_WRITECOMMAND(0x14); //
        SSD1306_WRITECOMMAND(0xAF); //--turn on SSD1306 panel

        TM_SSD1306_Fill_My();
        TM_SSD1306_UpdateScreenMy();

	while (1) {
	}
}

