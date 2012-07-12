#ifndef __MT12864_CONNECTION_H
#define __MT12864_CONNECTION_H


/*--------------------------------------------------------------------------------------------*/
/* LCD control lines are attached to port C                                                   */
/*--------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------*/
/* Line E connected to PC0.                                                                   */
/* Active level - high                                                                        */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_E               0

/*--------------------------------------------------------------------------------------------*/
/* Line A0 (data/command) is connected to PC1.                                                */
/* "1" - data transmission, "0" - command transmission.                                       */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_A0              1

/*--------------------------------------------------------------------------------------------*/
/* Line RW (read/write) is connected to PC2.                                                  */
/* "1" - read cycle, "0" - write cycle.                                                       */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_RW              2

/*--------------------------------------------------------------------------------------------*/
/* Line CS2 (select chip 2) is connected to PC3.                                              */
/* Active level - low                                                                         */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_CS2             3

/*--------------------------------------------------------------------------------------------*/
/* Line CS1 (select chip 1) is connected to PC4.                                              */
/* Active level - low                                                                         */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_CS1             4

/*--------------------------------------------------------------------------------------------*/
/* Line RES (reset) is connected to PC5.                                                      */
/* Active level - low                                                                         */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_RES             5

/*--------------------------------------------------------------------------------------------*/
/* Backlight control is connected to PC6.                                                     */
/* "1" - backlight on, "0" - backlight off.                                                   */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_BACKLIGHT         6





#define mt12864_clear_line(pin) cbi(PORTC, (pin))
//#define clear_lines_in_lcd_control_port(mask) PORTC &= ~(mask)
#define mt12864_set_line(pin) sbi(PORTC, (pin))
//#define set_lines_in_lcd_control_port(mask) PORTC |= (mask)

#define mt12864_is_line_set(pin) bit_is_set(PINC, (pin))


#define mt12864_clear_line_E   mt12864_clear_line(LCD_E)
#define mt12864_clear_line_RW  mt12864_clear_line(LCD_RW)
#define mt12864_clear_line_A0  mt12864_clear_line(LCD_A0)
#define mt12864_clear_line_RES mt12864_clear_line(LCD_RES)
#define mt12864_set_line_E     mt12864_set_line(LCD_E)
#define mt12864_set_line_RW    mt12864_set_line(LCD_RW)
#define mt12864_set_line_A0    mt12864_set_line(LCD_A0)
#define mt12864_set_line_RES   mt12864_set_line(LCD_RES)


// This ternary construct is more efficient - compiles to 10 bytes
#define mt12864_clear_cs(chip) (chip == 0) ? (mt12864_clear_line(LCD_CS1)) : (mt12864_clear_line(LCD_CS2))
#define mt12864_set_cs {mt12864_set_line(LCD_CS1); mt12864_set_line(LCD_CS2); }

#define mt12864_backlight_on()    mt12864_clear_line(LCD_BACKLIGHT_PIN)
#define mt12864_backlight_off()   mt12864_set_line(LCD_BACKLIGHT)
#define is_mt12864_backlight_on() mt12864_is_line_set(LCD_BACKLIGHT_PIN)


#define mt12864_configure_ports() do {\
  sbi(DDRC, LCD_E);\
  sbi(DDRC, LCD_RW);\
  sbi(DDRC, LCD_A0);\
  sbi(DDRC, LCD_CS2);\
  sbi(DDRC, LCD_CS1);\
  sbi(DDRC, LCD_RES);\
  sbi(DDRC, LCD_BACKLIGHT);\
} while(0)

#define mt12864_clear_all_control_lines() do {\
  mt12864_clear_line (LCD_E);\
  mt12864_clear_line (LCD_RW);\
  mt12864_clear_line (LCD_A0);\
  mt12864_clear_line (LCD_CS2);\
  mt12864_clear_line (LCD_CS1);\
  mt12864_clear_line (LCD_RES);\
  mt12864_clear_line (LCD_BACKLIGHT);\
} while(0)

/*--------------------------------------------------------------------------------------------*/
/* LCD data bus is connected to Port B.                                                       */
/*--------------------------------------------------------------------------------------------*/
#define LCD_Data_Bus_to_Output()        DDRB = 0xff
#define LCD_Data_Bus_To_Input()         { DDRB = 0x00; PORTB = 0xff; }
#define Put_Data_to_LCD_Data_Bus(data)  PORTB = (data)
#define Get_Data_from_LCD_Data_Bus()    PINB



#endif