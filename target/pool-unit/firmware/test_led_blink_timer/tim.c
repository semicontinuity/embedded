#include "tim.h"


TIM_HandleTypeDef htim4;


void MX_TIM4_Init(void)
{
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = (uint32_t)(SystemCoreClock / 10000) - 1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 10000 - 1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_Base_Start_IT(&htim4) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_icHandle)
{
  if(tim_icHandle->Instance==TIM4)
  {
    __HAL_RCC_TIM4_CLK_ENABLE();

    /*##-2- Configure the NVIC for TIMx ########################################*/
    /* Set the TIMx priority */
    HAL_NVIC_SetPriority(TIM4_IRQn, 3, 0);

    /* Enable the TIMx global Interrupt */
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
  }
}


void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_icHandle)
{
  if(tim_icHandle->Instance==TIM4)
  {
    __HAL_RCC_TIM4_CLK_DISABLE();
  }
} 
