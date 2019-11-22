#include "stm32fxxx_hal.h"
#include "defines.h"
#include <tm_stm32_delay.h>
#include "app_lcd.h"

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
    TM_DELAY_Init();

    select_lcd(0);
    APP_LCD_Init(0);
    lcd_puts(1, 1, "Hello, world!");

    while (1) {
    }
}

