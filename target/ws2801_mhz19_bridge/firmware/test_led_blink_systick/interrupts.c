#include "includes.h"


void NMI_Handler(){}
void HardFault_Handler(){while (1){};}
void MemManage_Handler(){while (1){};}
void BusFault_Handler(){while (1){};}
void UsageFault_Handler(){while (1){};}
void SVC_Handler(){}
void DebugMon_Handler(){}
void PendSV_Handler(){}
void SDIO_IRQHandler(){}
void TIM1_CC_IRQHandler() {}


void SysTick_Handler() {
    on_sys_tick();
}


void TIM2_IRQHandler(){}

void EXTI0_IRQHandler(){}
void EXTI2_IRQHandler(){}
