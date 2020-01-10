#include <mios32.h>

#include <FreeRTOS.h>
#include <task.h>

#define PRIORITY_TASK_SCAN_HID_BOARDS (tskIDLE_PRIORITY + 3)

#include <string.h>


s32 i2c_transfer(u8 port, u8 iic_addr, u8 *buffer, size_t size, mios32_iic_transfer_t transfer_type) {
    s32 status;

    if((status=MIOS32_IIC_TransferBegin(port, IIC_Blocking)) < 0)
        MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_TransferBegin failed with %d!\n", port, status);
    else {
        if((status=MIOS32_IIC_Transfer(port, transfer_type, iic_addr, buffer, size)) < 0)
            MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_Transfer failed with %d!\n", port, status);
        else {
            if((status=MIOS32_IIC_TransferWait(port)) < 0)
                MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_TransferWait failed with %d!\n", port, status);
            else
                MIOS32_IIC_TransferFinished(port);
        }
    }

    return status;
}


volatile u8 buffer[4] = {0x01, 0xFF, 0xFF, 0x00};

s32 I2C_Comm_Send(u8 board) {
    buffer[0] = 1;
    buffer[1] = 0xFF;
    return i2c_transfer(
            MIOS32_IIC_IO_PORT,
            (MIOS32_IIC_IO_BASE_ADDRESS + board) << 1U,
            &buffer[0],
            4,
            IIC_Write);
}

static void TASK_CommunicateWithHIDBoards(void *pvParameters)  {
    portTickType xLastExecutionTime;

    // Initialise the xLastExecutionTime variable on task entry
    xLastExecutionTime = xTaskGetTickCount();

    while(1)  {
        vTaskDelayUntil(&xLastExecutionTime, 1000 / portTICK_RATE_MS);

/*
        I2C_Comm_Send(0);
        I2C_Comm_Send(1);
        I2C_Comm_Send(2);
        I2C_Comm_Send(3);
*/
    }
}


s32 I2C_Comm_Idle(void)
{
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
// Function to initialize SEQ Modifications
/////////////////////////////////////////////////////////////////////////////
s32 I2C_Comm_Init(u32 mode)
{
    MIOS32_IIC_Init(0);

    xTaskCreate(
            TASK_CommunicateWithHIDBoards,
            (const portCHAR *) "ScanHIDBoards",
            configMINIMAL_STACK_SIZE,
            NULL,
            PRIORITY_TASK_SCAN_HID_BOARDS,
            NULL
    );

    return 0;
}
