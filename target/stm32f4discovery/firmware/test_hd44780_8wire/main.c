#include "stm32fxxx_hal.h"
#include "defines.h"
#include <tm_stm32_delay.h>
#include "app_lcd.h"

int main(void) {
    TM_RCC_InitSystem();
    HAL_Init();
    TM_DELAY_Init();

    select_lcd(0);
    APP_LCD_Init(0);
    APP_LCD_Data('D');
    APP_LCD_Data('0');

    select_lcd(1);
    APP_LCD_Init(0);
    APP_LCD_Data('D');
    APP_LCD_Data('1');

    select_lcd(2);
    APP_LCD_Init(0);
    APP_LCD_Data('D');
    APP_LCD_Data('2');

    select_lcd(3);
    APP_LCD_Init(0);
    APP_LCD_Data('D');
    APP_LCD_Data('3');

    while (1) {
    }
}

