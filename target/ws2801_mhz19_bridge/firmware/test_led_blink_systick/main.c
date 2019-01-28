#include "stm32f10x.h"


static __IO uint32_t delay;


// Clocks
void RCC_Config(void) {
    ErrorStatus HSEStartUpStatus;
    // Configuration of SYSCLK, HCLK, PCLK2 + PCLK1
    RCC_DeInit();
    RCC_HSEConfig(RCC_HSE_ON);
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if (HSEStartUpStatus == SUCCESS) {
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        RCC_PCLK2Config(RCC_HCLK_Div1);
        RCC_PCLK1Config(RCC_HCLK_Div2);
        // PLLCLK = 8MHz * 9 = 72 MHz
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
        RCC_PLLCmd(ENABLE);
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        while (RCC_GetSYSCLKSource() != 0x08) {}

        /* Enable GPIOA clock */
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
    } else {
        // HSE start error - clock configuration will be wrong
        // maybe say about it?
        while (1) {}
    }
}

/*
 * System setup
 */
void Set_System(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_Config();

    /* Configure PC.13 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}


void delay_ms(__IO uint32_t value) {
    delay = value;
    while (delay != 0);
}


void on_sys_tick(void) {
    if (delay != 0) {
        --delay;
    }
}


int main(void) {
    Set_System();
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);
    }

    while (1) {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        delay_ms(1000);

        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        delay_ms(3000);
    }
}