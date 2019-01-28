/*
 * Based on ST Microelectronics STM32 examples
 */

#include <usb_lib.h>
#include <string.h>
#include "hw_config.h"
#include "usb_regs.h"
#include "usb_lib.h"
#include "usb_istr.h"

uint8_t usb_endpoint_handler__buffer[64];


extern __IO uint8_t PrevXferComplete;


void EP1_OUT_Callback(void) {
    USB_SIL_Read(EP1_OUT, usb_endpoint_handler__buffer);
    GPIO_Write(GPIOA, (uint16_t) usb_endpoint_handler__buffer[0]);
    SetEPRxStatus(ENDP1, EP_RX_VALID);
}


void EP1_IN_Callback(void) {
    PrevXferComplete = 1;
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}
