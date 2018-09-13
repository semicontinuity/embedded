/*
 * Based on ST Microelectronics STM32 examples
 */

#include <usb_lib.h>

uint8_t Receive_Buffer[64];
extern __IO uint8_t PrevXferComplete;
uint8_t flag;


void EP1_OUT_Callback(void) {
    if (flag) {
        flag = 0;
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    } else {
        flag = 1;
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
    }

    USB_SIL_Read(EP1_OUT, Receive_Buffer);
    SetEPRxStatus(ENDP1, EP_RX_VALID);
}


void EP1_IN_Callback(void) {
    PrevXferComplete = 1;
}
