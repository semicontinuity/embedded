#include "includes.h"

static __IO uint32_t delay;


GPIO_InitTypeDef GPIO_InitStructure;
__IO uint8_t PrevXferComplete = 1;

__IO uint8_t some_data[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};


void usart1__init() {
    /* Enable peripheral clocks for USART1 on GPIOB */
    RCC_APB2PeriphClockCmd(
        RCC_APB2Periph_USART1 |
        RCC_APB2Periph_GPIOB |
        RCC_APB2Periph_AFIO, ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

    /* Configure PB6 and PB7 as USART1 TX/RX */

    /* PB6 = alternate function push/pull output */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* PB7 = pull-up input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Configure and initialize usart... */
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);

    /* Enable USART1 */
    USART_Cmd(USART1, ENABLE);
}


inline void Set_System(void) {
    RCC_Config();

    /* Enable GPIOC clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    /* Configure PC.13 as Output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);


    Set_USBClock();
    USB_Interrupts_Config();
    USB_Init();

    usart1__init();
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


void delay_ms(__IO uint32_t value) {
    timer__set(value);
    while (timer__is_running());
}

void on_sys_tick(void) {
    if (delay != 0) {
        --delay;
    }
}


__IO uint8_t mhz19_request[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
__IO uint8_t *mhz19_response = some_data;
//uint8_t mhz19_response[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


int mhz19_response_ok(void) {
    if (mhz19_response[0] != 0xFF) return 0;
    if (mhz19_response[1] != 0x86) return 0;

    uint8_t check_sum = 0x00;
    for (int i = 1; i < 8; i++) {
        check_sum += mhz19_response[i];
    }
    check_sum ^= 0xFF;
    check_sum += 0x01;
    return check_sum == mhz19_response[8] ? 1 : 0;
}


void read_sensor() {
    for (int i = 0; i < 9; i++) {
        USART_SendData(USART1, mhz19_request[i]);
        /* Wait until the byte has been transmitted */
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
    
    // Read up to 9 bytes within 600ms
    timer__set(600);
    int i = 0;
    while (1) {
        if (timer__is_expired()) {
            if (i == 9) {
                some_data[15] = (uint8_t) 0x01;

                uint8_t h = mhz19_response[2];
                uint8_t l = mhz19_response[3];
                some_data[16] = l;
                some_data[17] = h;

                some_data[14] = (uint8_t) mhz19_response_ok();
            } else {
                some_data[15] = 0;
                some_data[16] = 0;
                some_data[17] = 0;
                some_data[14] = 0;
            }

            return;
        }

        if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) {
            uint8_t a_byte = (uint8_t) USART_ReceiveData(USART1);   // read anyway
            if (i < 9) {
                mhz19_response[i++] = a_byte;
            }
        }
    }
}


int main(void) {
    Set_System();
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);
    }


    for (;;) {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        read_sensor();
        GPIO_SetBits(GPIOC, GPIO_Pin_13);

        if (bDeviceState == CONFIGURED) {
            if (PrevXferComplete) {
                PrevXferComplete = 0;
                USB_SIL_Write(EP1_IN, (uint8_t*) some_data, 64);
                SetEPTxValid(ENDP1);
            }
        }

        delay_ms(10000);
    }
}
