//Atmega8A - используемый микроконтроллер
//#define F_CPU 8000000
#include <util/delay.h>
#include <stdlib.h>
//#include 
//объявим  библиотеку
#include "n5110.h"
 
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"


int main(void)
{
    usart0__init();
    usart0__tx__enabled__set(1);
        Lcd_init();
    while(1)
    {


/*
        //согласно шпаргалке 
        //очистим дисплей
        Lcd_clear();
        //Lcd_prints для вывода статичных данных
        Lcd_prints(0, 0, FONT_1X,(unsigned char *)PSTR("Привет!"));
        //Lcd_print для вывода из переменной
        Lcd_print(0, 1, FONT_1X,(unsigned char *)s_data);
        //Lcd_printf для вывода дробного числа (преобразование float в string)
        //2 - число знаков после зяпятой
        Lcd_printf(0, 2, FONT_1X, f_data, 2);
        //Для вывода числа преобразуем его в строку при помощи встроенной 
        //функции itoa(число, массив,система счисления)
        char buff[20];
        itoa(i_data, buff, 10);
        Lcd_print(0, 3, FONT_1X,(unsigned char *)buff);
        //передадим данные  
        Lcd_update();
        //подождем 2 секунды
        _delay_ms(2000);
        //очистим дисплей
        Lcd_clear();
        //Нарисуем кружки
        for (int i=0;i<=10;i++)
        {
            Lcd_circle(40, 24, i, PIXEL_ON);
        }
*/
        usart0__out__write('_');
        Lcd_fill(0x81);
        //передадим данные
        usart0__out__write('U');
        Lcd_update();
        //подождем 2 секунды
        _delay_ms(2000);

        usart0__out__write('F');
        Lcd_fill(0xFF);
        //передадим данные
        usart0__out__write('U');
        Lcd_update();
        //подождем 2 секунды
        _delay_ms(2000);

        usart0__out__write('.');
    }
}