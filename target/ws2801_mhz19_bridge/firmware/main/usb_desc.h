/*
 * Based on ST Microelectronics STM32 examples
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DESC_H
#define __USB_DESC_H

#include "stm32f10x.h"


/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05

#define HID_DESCRIPTOR_TYPE                     0x21
#define WILLBEHID_SIZ_HID_DESC                  0x09
#define WILLBEHID_OFF_HID_DESC                  0x12

#define WILLBEHID_SIZ_DEVICE_DESC               18
#define WILLBEHID_SIZ_CONFIG_DESC               41
#define WILLBEHID_SIZ_REPORT_DESC               163
#define WILLBEHID_SIZ_STRING_LANGID             4
#define WILLBEHID_SIZ_STRING_VENDOR             38
#define WILLBEHID_SIZ_STRING_PRODUCT            32
#define WILLBEHID_SIZ_STRING_SERIAL             26

#define STANDARD_ENDPOINT_DESC_SIZE             0x09

/* Exported functions ------------------------------------------------------- */
extern const uint8_t WillBeHID_DeviceDescriptor[WILLBEHID_SIZ_DEVICE_DESC];
extern const uint8_t WillBeHID_ConfigDescriptor[WILLBEHID_SIZ_CONFIG_DESC];
extern const uint8_t WillBeHID_ReportDescriptor[WILLBEHID_SIZ_REPORT_DESC];
extern const uint8_t WillBeHID_StringLangID[WILLBEHID_SIZ_STRING_LANGID];
extern const uint8_t WillBeHID_StringVendor[WILLBEHID_SIZ_STRING_VENDOR];
extern const uint8_t WillBeHID_StringProduct[WILLBEHID_SIZ_STRING_PRODUCT];
extern uint8_t WillBeHID_StringSerial[WILLBEHID_SIZ_STRING_SERIAL];

#endif /* __USB_DESC_H */
