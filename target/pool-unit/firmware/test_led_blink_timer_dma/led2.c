#include "led2.h"

void led2__init() {
  static GPIO_InitTypeDef  GPIO_InitStruct;
  LED2_GPIO_CLK_ENABLE();

  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  GPIO_InitStruct.Pin = LED2_PIN;
  HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
}


void led2__toggle() { HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN); }
