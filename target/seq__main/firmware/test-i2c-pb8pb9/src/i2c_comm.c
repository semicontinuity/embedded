#include <mios32.h>

#include <FreeRTOS.h>
#include <task.h>

#define PRIORITY_TASK_SCAN_HID_BOARDS (tskIDLE_PRIORITY + 3)

#include <string.h>


volatile u8 stall;
volatile u8 go1;
volatile u8 go2;

t_c_buf i2c_ev_buf = {
    .w_offset = 0,
    .r_offset = 0
};

t_c_buf i2c_er_buf = {
        .w_offset = 0,
        .r_offset = 0
};

void c_buf_put(t_c_buf *c_buf, u32 value) {
    u32 w_offset = c_buf->w_offset;
    c_buf->buffer[w_offset] = value;
    c_buf->w_offset = (w_offset + 1U) & 0x0FU;
}

u32 c_buf_get(t_c_buf *c_buf) {
    u32 r_offset = c_buf->r_offset;
    u32 value = c_buf->buffer[r_offset];
    if (value) {
        c_buf->buffer[r_offset] = 0;
        c_buf->r_offset = (r_offset + 1U) & 0x0FU;
    }
    return value;
}


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
    while(1) {
        u32 ev = c_buf_get(&i2c_ev_buf);
        if (ev) {
            MIOS32_MIDI_SendDebugMessage("IIC EV %08x\n", ev);
        }

        u32 er = c_buf_get(&i2c_er_buf);
        if (er) {
            MIOS32_MIDI_SendDebugMessage("IIC ER %08x\n", er);
        }

        if (stall) {
            stall = 0;
            MIOS32_MIDI_SendDebugMessage("IIC STALL\n", er);
        }
        if (go1) {
            go1 = 0;
            MIOS32_MIDI_SendDebugMessage("IIC GO1\n", er);
        }
        if (go2) {
            go2 = 0;
            MIOS32_MIDI_SendDebugMessage("IIC GO2\n", er);
        }
    }
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
