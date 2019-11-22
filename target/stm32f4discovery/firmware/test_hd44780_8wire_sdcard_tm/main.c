/**
 * Keil project for SDCARD reader using SDIO/SDMMC example
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

#include "app_lcd.h"

/* Include my libraries here */
#include "defines.h"
#include "tm_stm32_disco.h"
#include "tm_stm32_delay.h"
#include "tm_stm32_fatfs.h"
#include "stdio.h"

/* Fatfs structure */
FATFS FS;
FIL fil;
FRESULT fres;

/* Size structure for FATFS */
TM_FATFS_Size_t CardSize;

/* Buffer variable */
char buffer[100];

// no bounds checking
void lcd_puts(uint8_t x, uint8_t y, char* str) {
    APP_LCD_CursorSet(x, y);
    while (*str) {
        APP_LCD_Data(*str);
        str++;
    }
}


int main(void) {
    TM_RCC_InitSystem();
    HAL_Init();
    TM_DISCO_LedInit();
    TM_DELAY_Init();

    select_lcd(0);
    APP_LCD_Init(0);
    lcd_puts(0, 0, "Mounting SD Card");

    if (f_mount(&FS, "SD:", 1) == FR_OK) {
        lcd_puts(0, 1, "Mounted SD Card");

        if ((fres = f_open(&fil, "SD:first_file.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE)) == FR_OK) {
            lcd_puts(0, 2, "Opened file");

			TM_FATFS_GetDriveSize("SD:", &CardSize);
			
			/* Format string */
			sprintf(buffer, "Total card size: %u kBytes\n", CardSize.Total);
			
			/* Write total card size to file */
			f_puts(buffer, &fil);
			
			/* Format string for free card size */
			sprintf(buffer, "Free card size:  %u kBytes\n", CardSize.Free);
			
			/* Write free card size to file */
			f_puts(buffer, &fil);
			
			/* Close file */
			f_close(&fil);
			
			/* Turn led ON */
			TM_DISCO_LedOn(LED_ALL);
        } else {
            TM_DISCO_LedOn(LED_ORANGE);
            lcd_puts(0, 2, "Failed to open file");
        }

        f_mount(NULL, "SD:", 1);
    } else {
        TM_DISCO_LedOn(LED_RED);
        lcd_puts(0, 1, "Failed to mount card");
    }

    while (1) {
    }
}

