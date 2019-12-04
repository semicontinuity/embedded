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


void write_file() {
    lcd_puts(0, 0, "Opening file");
    if ((fres = f_open(&fil, "SD:hello.txt", FA_WRITE/*|FA_CREATE_ALWAYS|FA_CREATE_NEW*/)) != FR_OK) {
//    if ((fres = f_open(&fil, "SD:test.txt", FA_CREATE_NEW | FA_WRITE)) != FR_OK) {
        TM_DISCO_LedOn(LED_ORANGE);
        //f_open
        sprintf(buffer, "f_open failed: %u", fres);
        lcd_puts(0, 1, buffer);
        return;
    }
    lcd_puts(0, 1, "Opened file");

    char writeBuff[256];
    snprintf(writeBuff, sizeof(writeBuff),
             "Total blocks: %lu (%lu Mb); Free blocks: %lu (%lu Mb)\r\n",
             1, 2000 / 2000,
             2, 2000 / 2000);

    unsigned int bytesToWrite = strlen(writeBuff);
    unsigned int bytesWritten;
    lcd_puts(0, 0, "Writing file");
    fres = f_write(&fil, writeBuff, 256, &bytesWritten);
    if(fres != FR_OK) {
        TM_DISCO_LedOn(LED_GREEN);
        sprintf(buffer, "f_write failed: %u", fres);
        lcd_puts(0, 1, buffer);
        return;
    }

//    TM_DISCO_LedOn(LED_ALL);
//    buffer[12] = 0;
//    lcd_puts(0, 3, buffer);

/*
    Delayms(50);
    lcd_puts(0, 0, "Syncing file    ");
    fres = f_sync(&fil);
    if (fres != FR_OK) {
        TM_DISCO_LedOn(LED_BLUE);
        sprintf(buffer, "f_sync failed: %u", fres);
        lcd_puts(0, 1, buffer);
        return;
    }
*/

    Delayms(50);
    lcd_puts(0, 0, "Closing file    ");
    fres = f_close(&fil);
    if (fres != FR_OK) {
        TM_DISCO_LedOn(LED_BLUE);
        sprintf(buffer, "f_close failed: %u", fres);
        lcd_puts(0, 1, buffer);
        return;
    }
}


void read_file() {
    if ((fres = f_open(&fil, "SD:test.txt", FA_READ)) != FR_OK) {
        TM_DISCO_LedOn(LED_ORANGE);
        //f_open
        sprintf(buffer, "f_open failed: %u", fres);
        lcd_puts(0, 2, buffer);
        return;
    }
    lcd_puts(0, 2, "Opened file");

    unsigned int bytesRead;
    fres = f_read(&fil, buffer, 12, &bytesRead);
    if(fres != FR_OK) {
        TM_DISCO_LedOn(LED_GREEN);
        sprintf(buffer, "f_read failed: %u", fres);
        lcd_puts(0, 3, buffer);
        return;
    }

    TM_DISCO_LedOn(LED_ALL);
    buffer[12] = 0;
    lcd_puts(0, 3, buffer);

    lcd_puts(0, 0, "Closing file    ");
    fres = f_close(&fil);
    if (fres != FR_OK) {
        TM_DISCO_LedOn(LED_BLUE);
        sprintf(buffer, "f_close failed: %u", fres);
        lcd_puts(0, 1, buffer);
        return;
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
    if (f_mount(&FS, "SD:", 1) != FR_OK) {
        TM_DISCO_LedOn(LED_RED);
        lcd_puts(0, 1, "Failed to mount card");
        while (1) {}
    }
    lcd_puts(0, 1, "Mounted SD Card");

    write_file();

    lcd_puts(0, 2, "Unmounting card");
    fres = f_mount(NULL, "SD:", 1);
    if (fres != FR_OK) {
        TM_DISCO_LedOn(LED_RED);
        sprintf(buffer, "f_mount failed: %u", fres);
        lcd_puts(0, 3, buffer);
    }

    while (1) {}
}

