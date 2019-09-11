#ifndef LCD_H_
#define LCD_H_


#include <stdint.h>


#define PIN_E                 (   1 << 10)
#define PIN_RW                (   1 << 11)
#define PIN_RS                (   1 << 12)

#define LCD_E(x)              GPIOE->ODR = (GPIOE->ODR & ~PIN_E)  | (x ? PIN_E : 0);

/* pin RW setting to 0 or 1                                                   */
#define LCD_RW(x)             GPIOE->ODR = (GPIOE->ODR & ~PIN_RW) | (x ? PIN_RW : 0);

/* pin RS setting to 0 or 1                                                   */
#define LCD_RS(x)             GPIOE->ODR = (GPIOE->ODR & ~PIN_RS) | (x ? PIN_RS : 0);

/* Reading DATA pins                                                          */
#define LCD_DATA_IN           SWAP_DATA[(((GPIOE->IDR & PINS_DATA) >> 4) & 0x0F)]

/* Writing value to DATA pins                                                 */
#define LCD_DATA_OUT(x)       GPIOE->ODR = (GPIOE->ODR & ~PINS_DATA) | ((SWAP_DATA[x]) << 4);


#define d4_set() GPIOE->ODR = (GPIOE->ODR & ~(1 << 7))  | (1 << 7)
#define d5_set() GPIOE->ODR = (GPIOE->ODR & ~(1 << 6))  | (1 << 6)
#define d6_set() GPIOE->ODR = (GPIOE->ODR & ~(1 << 5))  | (1 << 5)
#define d7_set() GPIOE->ODR = (GPIOE->ODR & ~(1 << 4))  | (1 << 4)

#define d4_reset() GPIOE->ODR = (GPIOE->ODR & ~(1 << 7)) 
#define d5_reset() GPIOE->ODR = (GPIOE->ODR & ~(1 << 6))
#define d6_reset() GPIOE->ODR = (GPIOE->ODR & ~(1 << 5))
#define d7_reset() GPIOE->ODR = (GPIOE->ODR & ~(1 << 4))

#define e1 LCD_E(1)
#define e0 LCD_E(0)

#define rs1 LCD_RS(1)
#define rs0 LCD_RS(0)


//------------------------------------------------
void LCD_ini(void);
void LCD_Clear(void);
void LCD_SendChar(char ch);
void LCD_String(char* st);
void LCD_SetPos(uint8_t x, uint8_t y);
//------------------------------------------------
#endif /* LCD_H_ */
