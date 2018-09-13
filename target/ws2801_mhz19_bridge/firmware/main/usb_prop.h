/*
 * Based on ST Microelectronics STM32 examples
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_PROP_H
#define __USB_PROP_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum _HID_REQUESTS
{
  GET_REPORT = 1,
  GET_IDLE,
  GET_PROTOCOL,

  SET_REPORT = 9,
  SET_IDLE,
  SET_PROTOCOL
} HID_REQUESTS;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void WillBeHID_init(void);
void WillBeHID_Reset(void);
void WillBeHID_SetConfiguration(void);
void WillBeHID_SetDeviceAddress (void);
void WillBeHID_Status_In (void);
void WillBeHID_Status_Out (void);
RESULT WillBeHID_Data_Setup(uint8_t);
RESULT WillBeHID_NoData_Setup(uint8_t);
RESULT WillBeHID_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *WillBeHID_GetDeviceDescriptor(uint16_t );
uint8_t *WillBeHID_GetConfigDescriptor(uint16_t);
uint8_t *WillBeHID_GetStringDescriptor(uint16_t);
RESULT WillBeHID_SetProtocol(void);
uint8_t *WillBeHID_GetProtocolValue(uint16_t Length);
RESULT WillBeHID_SetProtocol(void);
uint8_t *WillBeHID_GetReportDescriptor(uint16_t Length);
uint8_t *WillBeHID_GetHIDDescriptor(uint16_t Length);


/* Exported define -----------------------------------------------------------*/
#define WillBeHID_GetConfiguration          NOP_Process
//#define WillBeHID_SetConfiguration          NOP_Process
#define WillBeHID_GetInterface              NOP_Process
#define WillBeHID_SetInterface              NOP_Process
#define WillBeHID_GetStatus                 NOP_Process
#define WillBeHID_ClearFeature              NOP_Process
#define WillBeHID_SetEndPointFeature        NOP_Process
#define WillBeHID_SetDeviceFeature          NOP_Process
//#define WillBeHID_SetDeviceAddress          NOP_Process

#define REPORT_DESCRIPTOR                  0x22

#endif /* __USB_PROP_H */
