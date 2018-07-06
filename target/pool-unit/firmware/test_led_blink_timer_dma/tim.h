#ifndef __tim_H
#define __tim_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef htim4;

extern void Error_Handler(void);

void MX_TIM4_Init(void);

#ifdef __cplusplus
}
#endif
#endif /*__ tim_H */
