/*
 * Local MIOS32 configuration file
 *
 * this file allows to disable (or re-configure) default functions of MIOS32
 * available switches are listed in $MIOS32_PATH/modules/mios32/MIOS32_CONFIG.txt
 *
 */

#ifndef _MIOS32_CONFIG_H
#define _MIOS32_CONFIG_H

extern volatile u8 stall;
extern volatile u8 go1;
extern volatile u8 go2;

typedef struct {
    volatile u32 buffer[16];
    volatile u32 w_offset;
    volatile u32 r_offset;
} t_c_buf;

extern t_c_buf i2c_ev_buf;
extern t_c_buf i2c_er_buf;

extern void c_buf_put(t_c_buf *c_buf, u32 value);
extern u32 c_buf_get(t_c_buf *c_buf);


#define MIOS32_IIC_TIMEOUT_VALUE 50000

#define MIOS32_IIC_NUM 2
#define MIOS32_IIC0_ENABLED 0
#define MIOS32_IIC1_ENABLED 1
#define MIOS32_IIC1_BUS_FREQUENCY 100000

#define MIOS32_IIC1_SCL_PORT    GPIOB
#define MIOS32_IIC1_SCL_PIN     GPIO_Pin_8
#define MIOS32_IIC1_SCL_AF      { GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1); }
#define MIOS32_IIC1_SDA_PORT    GPIOB
#define MIOS32_IIC1_SDA_PIN     GPIO_Pin_9
#define MIOS32_IIC1_SDA_AF      { GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1); }

#define MIOS32_IIC_IO_PORT 1
#define MIOS32_IIC_IO_BASE_ADDRESS 0x30U

#define MIOS32_DONT_USE_AOUT
#define MIOS32_DONT_USE_BOARD_J5
#define MIOS32_DONT_USE_BOARD_J10
#define MIOS32_DONT_USE_BOARD_J28
#define MIOS32_DONT_USE_BOARD_J15
#define MIOS32_DONT_USE_BOARD_DAC
#define MIOS32_DONT_USE_BOARD_LED

#define MIOS32_DONT_USE_DIN
#define MIOS32_DONT_USE_COM
#define MIOS32_DONT_USE_AIN
#define MIOS32_DONT_USE_DOUT
#define MIOS32_DONT_USE_ENC
//#define MIOS32_DONT_USE_LCD
#define MIOS32_DONT_USE_SRIO
#define MIOS32_DONT_USE_UART
#define MIOS32_DONT_USE_SDCARD
#define MIOS32_DONT_USE_ENC28J60
#define MIOS32_DONT_USE_SPI
#define MIOS32_DONT_USE_SPI0
#define MIOS32_DONT_USE_SPI1
#define MIOS32_DONT_USE_SPI2
#define MIOS32_DONT_USE_OSC
#define MIOS32_DONT_USE_MF
#define MIOS32_DONT_USE_IIC_BS
#define MIOS32_DONT_USE_IIC_MIDI
#define MIOS32_DONT_USE_UART_MIDI
#define MIOS32_DONT_USE_SPI_MIDI

#define LCD_NUM_DEVICES          1
#define LCD_COLUMNS_PER_DEVICE  20

#define MIOS32_CLCD_PARALLEL_DISPLAYS 1

#define MIOS32_CLCD_PARALLEL_LCD0_RS_PORT GPIOD
#define MIOS32_CLCD_PARALLEL_LCD0_RS_PIN GPIO_Pin_0
#define MIOS32_CLCD_PARALLEL_LCD0_RW_PORT GPIOD
#define MIOS32_CLCD_PARALLEL_LCD0_RW_PIN GPIO_Pin_7
#define MIOS32_CLCD_PARALLEL_LCD0_E_PORT GPIOD
#define MIOS32_CLCD_PARALLEL_LCD0_E_PIN GPIO_Pin_1
#define MIOS32_CLCD_PARALLEL_LCD0_DATA_PORT GPIOE
#define MIOS32_CLCD_PARALLEL_LCD0_DATA_PINS_OFFSET 8U

#define MIOS32_USB_PRODUCT_STR  "test-i2c-pb8pb9"

#endif /* _MIOS32_CONFIG_H */
