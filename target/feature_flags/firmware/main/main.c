#include "includes.h"

static __IO uint32_t delay;


GPIO_InitTypeDef GPIO_InitStructure;
__IO uint8_t PrevXferComplete = 1;

__IO uint8_t some_data[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};

__IO uint16_t latest_buttons_state = 0xFFFF;
__IO uint8_t latest_buttons_bits = 0x00;
__IO uint8_t has_pad_event = 0;

void initOutputPins0_7(GPIO_TypeDef *port);
void initInputPins8_15(GPIO_TypeDef *port);


inline void Set_System(void) {
    RCC_Config();

    /* Enable GPIOC clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    /* Configure PC.13 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    initOutputPins0_7(GPIOA);
    initInputPins8_15(GPIOB);

    Set_USBClock();
    USB_Interrupts_Config();
    USB_Init();
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

void pad_reader__run() {
    uint16_t current_buttons_state = GPIO_ReadInputData(GPIOB);
    if (current_buttons_state == latest_buttons_state) {    // stable for 1 tick
        uint8_t new_bits = (uint8_t) ~(current_buttons_state >> 8);
        if (new_bits != latest_buttons_bits && !has_pad_event) {
            latest_buttons_bits = new_bits;
            some_data[0] = new_bits;
            has_pad_event = 1;
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        }
    }
    latest_buttons_state = current_buttons_state;
/*
    uint16_t current_buttons_state = GPIO_ReadInputData(GPIOB);
    if (current_buttons_state == latest_buttons_state) {    // stable for 1 tick
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        some_data[0] = (uint8_t) ~(current_buttons_state >> 8);
        has_pad_event = 1;
    }
    latest_buttons_state = current_buttons_state;
*/
}


int main(void) {
    Set_System();
    if (SysTick_Config(SystemCoreClock / 100)) {
        while (1);
    }


    for (;;) {
        pad_reader__run();

        if (bDeviceState == CONFIGURED) {
            if (PrevXferComplete && has_pad_event) {
                PrevXferComplete = 0;
                has_pad_event = 0;
                USB_SIL_Write(EP1_IN, (uint8_t*) some_data, 64);
                SetEPTxValid(ENDP1);
            }
        }

        delay_ticks(1);
    }
}
