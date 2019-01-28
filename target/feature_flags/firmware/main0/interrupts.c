/*
 * Based on ST Microelectronics STM32 examples
 */

#include "includes.h"

// sync USART buffer to USB every IN_FRAME_INTERVAL SOF packets
#define IN_FRAME_INTERVAL			5

// buffer for input data
//uint8_t USB_Rx_Buffer[SomeDev_DATA_SIZE];

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

/*
 * peripherial interrupts
 */

void EXTI0_IRQHandler(){}
void EXTI2_IRQHandler(){}


// USB Low Priority / CAN RX0
void USB_LP_CAN1_RX0_IRQHandler(){
	USB_Istr();
}

// Start Of Frame callback (11-bit frame number)
void SOF_Callback(){

}
