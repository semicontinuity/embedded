#include "stm32fxxx_hal.h"
#include "defines.h"
#include <tm_stm32_delay.h>
#include "app_lcd.h"

int main(void) {
	TM_RCC_InitSystem();
	HAL_Init();
    TM_DELAY_Init();

    APP_LCD_Init(0);
    APP_LCD_Data('O');
    APP_LCD_Data('K');

	while (1) {
	}
}

