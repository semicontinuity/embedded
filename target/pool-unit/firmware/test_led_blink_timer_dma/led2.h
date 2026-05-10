#ifndef __LED2_H
#define __LED2_H


#include "stm32f1xx_hal.h"

#define LED2_PIN                         GPIO_PIN_13
#define LED2_GPIO_PORT                   GPIOC
#define LED2_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()  
#define LED2_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOC_CLK_DISABLE()  

void led2__init();

void led2__toggle();


#endif
