#include "includes.h"

static __IO uint32_t delay;

GPIO_InitTypeDef GPIO_InitStructure;

__IO uint8_t PrevXferComplete = 1;
__IO uint8_t some_data[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};

__IO uint16_t latest_buttons_state = 0xFFFF;


void initOutputPins0_7(GPIO_TypeDef *port);
void initInputPins8_15(GPIO_TypeDef *port);

inline void Set_System(void) {
    RCC_Config();

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /* Configure PC.13 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    initOutputPins0_7(GPIOA);
    initInputPins8_15(GPIOB);

    Set_USBClock();
    USB_Interrupts_Config();
    USB_Init();
}

void initOutputPins0_7(GPIO_TypeDef *port) {
    /* Configure PA.0 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PA.1 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PA.2 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PA.3 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PA.4 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PA.5 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PA.6 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PA.7 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);
}

void initInputPins8_15(GPIO_TypeDef *port) {
    /* Configure PB.8 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PB.9 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PB.10 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PB.11 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PB.12 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PB.13 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PB.14 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    /* Configure PB.15 as input with pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);
}


void timer__set(__IO uint32_t value) {
    delay = value;
}

bool timer__is_running() {
    return delay != 0;
}

bool timer__is_expired() {
    return delay == 0;
}


void delay_ticks(__IO uint32_t value) {
    timer__set(value);
    while (timer__is_running());
}

void on_sys_tick(void) {
    if (delay != 0) {
        --delay;
    }

/*    uint16_t current_buttons_state  = GPIO_ReadInputData(GPIOB);
    if (current_buttons_state == latest_buttons_state) {    // stable for 1 tick
        uint8_t button_bits = (uint8_t) current_buttons_state >> 8;
        some_data[0] = button_bits;
        
        if (button_bits != 0) {
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        } else {
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
        }
        
        if (bDeviceState == CONFIGURED) {
            if (PrevXferComplete) {
                PrevXferComplete = 0;
                USB_SIL_Write(EP1_IN, (uint8_t*) some_data, 64);
                SetEPTxValid(ENDP1);
            }
        }
    }
    latest_buttons_state = current_buttons_state;*/
}


int main(void) {
    Set_System();
    if (SysTick_Config(SystemCoreClock / 100)) {
        while (1);
    }


    for (;;) {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        delay_ticks(100);

        uint16_t current_buttons_state  = GPIO_ReadInputData(GPIOB);
        GPIO_Write(GPIOA, current_buttons_state >> 8);

        if (bDeviceState == CONFIGURED) {
            if (PrevXferComplete) {
                PrevXferComplete = 0;

                some_data[0] = current_buttons_state & 0xFF;
                some_data[1] = current_buttons_state >> 8;

                USB_SIL_Write(EP1_IN, (uint8_t *) some_data, 64);
                SetEPTxValid(ENDP1);
            }
        }

        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        delay_ticks(100);
    }
}
