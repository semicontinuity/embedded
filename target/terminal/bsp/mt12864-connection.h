#ifndef __MT12864_CONNECTION_H
#define __MT12864_CONNECTION_H


/*--------------------------------------------------------------------------------------------*/
/* LCD control lines are attached to ports C and D                                            */
/*--------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------*/
/* Line E connected to PD6.                                                                   */
/* Active level - high                                                                        */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_E               6

/*--------------------------------------------------------------------------------------------*/
/* Line A0 (data/command) is connected to PC0.                                                */
/* "1" - data transmission, "0" - command transmission.                                       */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_A0              0

/*--------------------------------------------------------------------------------------------*/
/* Line RW (read/write) is connected to PD5.                                                  */
/* "1" - read cycle, "0" - write cycle.                                                       */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_RW              5

/*--------------------------------------------------------------------------------------------*/
/* Line CS2 (select chip 2) is connected to PC7. (not PC6?)                                   */
/* Active level - low                                                                         */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_CS2             7

/*--------------------------------------------------------------------------------------------*/
/* Line CS1 (select chip 1) is connected to PC6. (not PC7?)                                   */
/* Active level - low                                                                         */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_CS1             6

/*--------------------------------------------------------------------------------------------*/
/* Line RES (reset) is connected to PC1.                                                      */
/* Active level - low                                                                         */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_RES             1

/*--------------------------------------------------------------------------------------------*/
/* Backlight control is connected to PD7.                                                     */
/* "1" - backlight on, "0" - backlight off.                                                   */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_BACKLIGHT       7


#define mt12864_clear_line_E   cbi(PORTD,LCD_E)
#define mt12864_clear_line_RW  cbi(PORTD,LCD_RW)
#define mt12864_clear_line_A0  cbi(PORTC,LCD_A0)
#define mt12864_clear_line_RES cbi(PORTC,LCD_RES)
#define mt12864_clear_line_CS1 cbi(PORTC,LCD_CS1)
#define mt12864_clear_line_CS2 cbi(PORTC,LCD_CS2)

#define mt12864_set_line_E     sbi(PORTD,LCD_E)
#define mt12864_set_line_RW    sbi(PORTD,LCD_RW)
#define mt12864_set_line_A0    sbi(PORTC,LCD_A0)
#define mt12864_set_line_RES   sbi(PORTC,LCD_RES)
#define mt12864_set_line_CS1   sbi(PORTC,LCD_CS1)
#define mt12864_set_line_CS2   sbi(PORTC,LCD_CS2)

// This ternary construct is more efficient - compiles to 10 bytes
#define mt12864_clear_cs(chip) (chip == 0) ? (mt12864_clear_line_CS1) : (mt12864_clear_line_CS2)
#define mt12864_set_cs {mt12864_set_line_CS1; mt12864_set_line_CS2; }

#define mt12864_backlight_on()    sbi(PORTD,LCD_BACKLIGHT)
#define mt12864_backlight_off()   cbi(PORTD,LCD_BACKLIGHT)
#define is_mt12864_backlight_on() bit_is_set(PIND,LCD_BACKLIGHT)


#define mt12864_configure_ports() do {\
  sbi(DDRD, LCD_E);\
  sbi(DDRD, LCD_RW);\
  sbi(DDRC, LCD_A0);\
  sbi(DDRC, LCD_CS2);\
  sbi(DDRC, LCD_CS1);\
  sbi(DDRC, LCD_RES);\
  sbi(DDRD, LCD_BACKLIGHT);\
} while(0)

#define mt12864_clear_all_control_lines() do {\
  mt12864_clear_line_E;\
  mt12864_clear_line_RW;\
  mt12864_clear_line_A0;\
  mt12864_clear_line_CS2;\
  mt12864_clear_line_CS1;\
} while(0)

/*--------------------------------------------------------------------------------------------*/
/* LCD data bus is connected to Port A.                                                       */
/*--------------------------------------------------------------------------------------------*/
#define LCD_Data_Bus_to_Output()        DDRA = 0xff
#define LCD_Data_Bus_To_Input()         { DDRA = 0x00; PORTA = 0xff; }
#define Put_Data_to_LCD_Data_Bus(data)  PORTA = (data)
#define Get_Data_from_LCD_Data_Bus()    PINA



#endif