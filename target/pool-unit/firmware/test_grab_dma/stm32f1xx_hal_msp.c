#include <stm32f1xx_hal_gpio.h>
#include "main.h"


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  TIMx_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* TIM2 channel 2 pin (PA1) configuration */
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.Pin   = GPIO_PIN_1;
  GPIO_InitStructure.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull  = GPIO_PULLDOWN;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
  /*##-1- Reset peripherals ##################################################*/
  TIMx_FORCE_RESET();
  TIMx_RELEASE_RESET();
}
