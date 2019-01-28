#include "stm32f10x_it.h"
#include "tim.h"
#include "led2.h"

void NMI_Handler(void) {
}

void HardFault_Handler(void) {
    while (1) {
    }
}

void MemManage_Handler(void) {
    while (1) {
    }
}

void BusFault_Handler(void) {
    while (1) {
    }
}

void UsageFault_Handler(void) {
    while (1) {
    }
}

void SVC_Handler(void) {
}

void DebugMon_Handler(void) {
}

void PendSV_Handler(void) {
}

void SysTick_Handler(void) {
    HAL_IncTick();
}

void TIM4_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim4);
}


void DMA1_Channel7_IRQHandler(void)
{
    led2__toggle();
}

