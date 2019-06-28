## MidiBox SEQ V4 LCD connections

|                 |      | Conflict         |
|-----------------|------|------------------|
| LCD_D7          | PD7  | DIS0_RW          |
| LCD_SER_SCLK    | PD6  | USART2_RX        |
| LCD_SER_RCLK    | PD3  | DIS0_E           |
| LCD_RW          | PC11 | SDIO_D3          |
| LCD_RS          | PA8  | OTG_FS_SOF       |
| LCD_E1          | PC8  | SDIO_D0          |
| LCD_E2          | PC9  | SDIO_D1          |
