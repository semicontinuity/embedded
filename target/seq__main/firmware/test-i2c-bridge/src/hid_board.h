#ifndef _RGB_MATRIX_H
#define _RGB_MATRIX_H

#include <mios32.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include "midi_output_config.h"
#include "i2c.h"

//0x20 shifted by one to the left (mios specific)
#define MATRIX_MCU_IIC_ADDR 0x40

#define PRIORITY_TASK_BUTTON_MATRIX_SCAN (tskIDLE_PRIORITY + 3)

// Initialize the task which communicates with the RGB button matrix MCU
void APP_HIDBoard_Init(void);

// Process the change color messages from Ableton Live
void APP_HIDBoard_Process_Event(mios32_midi_package_t midi_package);

// called when a RGB matrix button press or depress has been detected
// creates and sends the corresponding MIDI message
void APP_HIDBoard_NotifyToggle(uint8_t button, uint8_t presses);

#endif
