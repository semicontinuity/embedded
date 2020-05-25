#include <mios32.h>
#include "app.h"


#include <FreeRTOS.h>
#include <task.h>

#define PRIORITY_TASK_SCAN_HID_BOARDS (tskIDLE_PRIORITY + 3)


#define I2C_PORT         1
#define SSD1306_I2C_ADDR 0x78
#define SSD1306_WIDTH    128
#define SSD1306_HEIGHT   64

static uint8_t buffer[1 + SSD1306_WIDTH];
static uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];


s32 i2c_transfer(u8 port, u8 iic_addr, u8 *buffer, size_t size, mios32_iic_transfer_t transfer_type) {
    s32 status;

    if ((status = MIOS32_IIC_TransferBegin(port, IIC_Blocking)) < 0)
        MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_TransferBegin failed with %d!\n", port, status);
    else {
        if ((status = MIOS32_IIC_Transfer(port, transfer_type, iic_addr, buffer, size)) < 0)
            MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_Transfer failed with %d!\n", port, status);
        else {
            if ((status = MIOS32_IIC_TransferWait(port)) < 0)
                MIOS32_MIDI_SendDebugMessage("IIC%d: MIOS32_IIC_TransferWait failed with %d!\n", port, status);
            else
                MIOS32_IIC_TransferFinished(port);
        }
    }

    return status;
}

/* Write command */
static void SSD1306_WRITECOMMAND(uint8_t command) {
    buffer[0] = command;
    i2c_transfer(I2C_PORT, SSD1306_I2C_ADDR, &buffer[0], 1, IIC_Write);
}



void TM_SSD1306_Fill_My(void) {
    /* Set memory */
    for (uint32_t offset = 0; offset < sizeof(SSD1306_Buffer); offset++) SSD1306_Buffer[offset] = 0xFFU;
}

void TM_SSD1306_UpdateScreenMy(void) {
    uint8_t m;

    for (m = 0; m < 8; m++) {
        SSD1306_WRITECOMMAND(0xB0 + m);
        SSD1306_WRITECOMMAND(0x00);
        SSD1306_WRITECOMMAND(0x10);

        buffer[0] = 0x40;
        for (uint32_t offset = 0; offset < SSD1306_WIDTH; offset++) {
            buffer[1 + offset] = SSD1306_Buffer[SSD1306_WIDTH * m + offset];
        };
        i2c_transfer(I2C_PORT, SSD1306_I2C_ADDR, &buffer[0], SSD1306_WIDTH, IIC_Write);
    }
}


static void comm(void) {
    /* Init LCD */
    SSD1306_WRITECOMMAND(0xAE); //display off
    SSD1306_WRITECOMMAND(0x20); //Set Memory Addressing Mode...
    SSD1306_WRITECOMMAND(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    SSD1306_WRITECOMMAND(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
    SSD1306_WRITECOMMAND(0xC8); //Set COM Output Scan Direction
    SSD1306_WRITECOMMAND(0x00); //---set low column address
    SSD1306_WRITECOMMAND(0x10); //---set high column address
    SSD1306_WRITECOMMAND(0x40); //--set start line address
    SSD1306_WRITECOMMAND(0x81); //--set contrast control register
    SSD1306_WRITECOMMAND(0xFF);
    SSD1306_WRITECOMMAND(0xA1); //--set segment re-map 0 to 127
    SSD1306_WRITECOMMAND(0xA6); //--set normal display
    SSD1306_WRITECOMMAND(0xA8); //--set multiplex ratio(1 to 64)
    SSD1306_WRITECOMMAND(0x3F); //
    SSD1306_WRITECOMMAND(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    SSD1306_WRITECOMMAND(0xD3); //-set display offset
    SSD1306_WRITECOMMAND(0x00); //-not offset
    SSD1306_WRITECOMMAND(0xD5); //--set display clock divide ratio/oscillator frequency
    SSD1306_WRITECOMMAND(0xF0); //--set divide ratio
    SSD1306_WRITECOMMAND(0xD9); //--set pre-charge period
    SSD1306_WRITECOMMAND(0x22); //
    SSD1306_WRITECOMMAND(0xDA); //--set com pins hardware configuration
    SSD1306_WRITECOMMAND(0x12);
    SSD1306_WRITECOMMAND(0xDB); //--set vcomh
    SSD1306_WRITECOMMAND(0x20); //0x20,0.77xVcc
    SSD1306_WRITECOMMAND(0x8D); //--set DC-DC enable
    SSD1306_WRITECOMMAND(0x14); //
    SSD1306_WRITECOMMAND(0xAF); //--turn on SSD1306 panel

    TM_SSD1306_Fill_My();
    TM_SSD1306_UpdateScreenMy();
}


static void TASK_CommunicateWithHIDBoards(void *pvParameters)  {
    portTickType xLastExecutionTime;

    // Initialise the xLastExecutionTime variable on task entry
    xLastExecutionTime = xTaskGetTickCount();

    while(1)  {
        vTaskDelayUntil(&xLastExecutionTime, 10 / portTICK_RATE_MS);
        comm();
    }
}


/////////////////////////////////////////////////////////////////////////////
// Function to initialize SEQ Modifications
/////////////////////////////////////////////////////////////////////////////
s32 SEQ_Mod_Init(u32 mode)
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

/////////////////////////////////////////////////////////////////////////////
// This hook is called after startup to initialize the application
/////////////////////////////////////////////////////////////////////////////
void APP_Init(void) {
    // initialize all LEDs
    MIOS32_BOARD_LED_Init(0xffffffff);

    SEQ_Mod_Init(0);
}



/////////////////////////////////////////////////////////////////////////////
// This task is running endless in background
/////////////////////////////////////////////////////////////////////////////
void APP_Background(void)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called each mS from the main task which also handles DIN, ENC
// and AIN events. You could add more jobs here, but they shouldn't consume
// more than 300 uS to ensure the responsiveness of buttons, encoders, pots.
// Alternatively you could create a dedicated task for application specific
// jobs as explained in $MIOS32_PATH/apps/tutorials/006_rtos_tasks
/////////////////////////////////////////////////////////////////////////////
void APP_Tick(void)
{
}

/////////////////////////////////////////////////////////////////////////////
// This hook is called each mS from the MIDI task which checks for incoming
// MIDI events. You could add more MIDI related jobs here, but they shouldn't
// consume more than 300 uS to ensure the responsiveness of incoming MIDI.
/////////////////////////////////////////////////////////////////////////////
void APP_MIDI_Tick(void)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a MIDI package has been received
/////////////////////////////////////////////////////////////////////////////
void APP_MIDI_NotifyPackage(mios32_midi_port_t port, mios32_midi_package_t midi_package) {
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called before the shift register chain is scanned
/////////////////////////////////////////////////////////////////////////////
void APP_SRIO_ServicePrepare(void)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called after the shift register chain has been scanned
/////////////////////////////////////////////////////////////////////////////
void APP_SRIO_ServiceFinish(void)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a button has been toggled
// pin_value is 1 when button released, and 0 when button pressed
/////////////////////////////////////////////////////////////////////////////
void APP_DIN_NotifyToggle(u32 pin, u32 pin_value)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when an encoder has been moved
// incrementer is positive when encoder has been turned clockwise, else
// it is negative
/////////////////////////////////////////////////////////////////////////////
void APP_ENC_NotifyChange(u32 encoder, s32 incrementer)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a pot has been moved
/////////////////////////////////////////////////////////////////////////////
void APP_AIN_NotifyChange(u32 pin, u32 pin_value)
{
}

