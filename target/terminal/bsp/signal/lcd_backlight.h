/*--------------------------------------------------------------------------------------------*/
/* Backlight control is connected to PD7.                                                     */
/* "1" - backlight on, "0" - backlight off.                                                   */
/*--------------------------------------------------------------------------------------------*/
#define   LCD_BACKLIGHT       7


#define mt12864_backlight_on()    sbi(PORTD,LCD_BACKLIGHT)
#define mt12864_backlight_off()   cbi(PORTD,LCD_BACKLIGHT)
#define is_mt12864_backlight_on() bit_is_set(PIND,LCD_BACKLIGHT)

#define mt12864_backlight_init()  do {\
  sbi(DDRD, LCD_BACKLIGHT);\
} while(0)
