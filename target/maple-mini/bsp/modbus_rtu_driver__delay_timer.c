// =============================================================================
// MODBUS RTU driver.
// Delay timer for handling of 1.5 and 3.5 character timeouts
// during USART data reception.
// =============================================================================

#include "modbus_rtu_driver__delay_timer.h"
#include <stm32f10x.h>
#include <stm32f10x_tim.h>


void modbus_rtu_driver__delay_timer__init(void) {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = MODBUS_RTU_DRIVER__DELAY_TIMER__PRESCALER;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = MODBUS_RTU_DRIVER__DELAY_TIMER__T15_VALUE;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = MODBUS_RTU_DRIVER__DELAY_TIMER__T35_VALUE;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);

    TIM_ARRPreloadConfig(TIM2, ENABLE);
    /* TIM IT enable */
    TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_CC2, ENABLE);
    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);
}


void modbus_rtu_driver__delay_timer__start(void) {
    TIM_SetCounter(TIM2, 0);
    TIM_Cmd(TIM2, ENABLE);
}


void modbus_rtu_driver__delay_timer__stop(void) {
    TIM_Cmd(TIM2, DISABLE);
}


void TIM2_IRQHandler(void)  {
    if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET) {
        // Invoked when 1.5 characters timeout expired.
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
        modbus_rtu_driver__delay_timer__on_t15_expired();
    }
    else if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET) {
        // Invoked when 3.5 characters timeout expired.
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
        modbus_rtu_driver__delay_timer__on_t35_expired();
    }
}
