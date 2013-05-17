//***************************************************************************
//
//  Author(s)...: Pashgan    http://ChipEnable.Ru   
//
//  Target(s)...: любая мега
//
//  Compiler....: IAR EWA 5.11A
//
//  Description.: драйвер графического индикатора МТ12232
//
//  Data........: 16.01.10 
//
//***************************************************************************
#ifndef LCD_GRAPH_LIB_H
#define LCD_GRAPH_LIB_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "cpu/avr/drivers/display/mt12232/bits_macros.h"

//****************************************************************************
//
//  ОБЯЗАТЕЛЬНЫЕ НАСТРОЙКИ
//
//частота тактирования мк
#ifndef F_CPU
  #define F_CPU 16000000
#endif

//порт к которому подключены управляющие сигналы
#define PORT_LCD_CON PORTD
#define PIN_LCD_CON  PIND
#define DDRX_LCD_CON DDRD

//порт к которому подключена шина данных 
#define PORT_LCD_BUS PORTB  
#define PIN_LCD_BUS  PINB
#define DDRX_LCD_BUS DDRB

//порт к которому подключен EN
#define PORT_LCD_EN  PORTC  
#define PIN_LCD_EN   PINC
#define DDRX_LCD_EN  DDRC

//порт к которому подключен RES
#define PORT_LCD_RES PORTC  
#define PIN_LCD_RES  PINC
#define DDRX_LCD_RES DDRC

//выводы к которым подключены управляющие сигналы жкд
#define RES     1
#define CS      1
#define AO      4
#define RD_WR   5
#define EN      2

//*****************************************************************************
//
//  МАКРООПРЕДЕЛЕНИЯ
//
//команды
#define COM_DISPLAY_ON       0xaf               //включает жкд
#define COM_DISPLAY_OFF      0xae               //выключает жкд
#define COM_START_LINE(x)    (0xc0&(0x1f&(x)))  //определяет верхнюю строку жкд
#define COM_ADC_SELECT_OFF   0xa0               //прямое соответствие адреса и позиции
#define COM_ADC_SELECT_ON    0xa1               //обратное соответствие адреса и позиции
#define COM_STATIC_DRIVE_ON  0xa5               //статический режим управления
#define COM_STATIC_DRIVE_OFF 0xa4               //обычное управление
#define COM_DUTY_SELECT_ON   0xa9               //выбор мультиплекса
#define COM_CLEAR_RMW        0xee               //снятие флага RMW
#define COM_SELECT_RMW       0xe0               //установка флага RMW
#define COM_RESET            0xe2               //строка и страница сбрасывается в 0

//методы вывода на экран
#define MET_AND  0
#define MET_OR   1
#define MET_XOR  2

#define FILL_OFF 0  //заполнения нет
#define FILL_ON  1  //заполнение есть

//******************************************************************************
//
//  ФУНКЦИИ
//
//низкоуровневые функции
unsigned char LCDG_ReadData(void);                       //чтение байта ОЗУ. перед использованием нужно установить адрес страницы и столбца
void LCDG_SendCom(unsigned char data);                   //запись команды
void LCDG_SendData(unsigned char data);                  //запись данных

//функции инициализации
extern void LCDG_InitPort(void);                                //инициализация порта вводавывода
void LCDG_InitLcd(void);                                 //инициализация lcd. подает последовательноть команд для обоих контроллеров модуля 
void LCDG_ClrDisp(unsigned char x1, unsigned char x2);   //очищает дисплей от x1 до x2
#define LCDG_ClrAllDisp() LCDG_ClrDisp(0, 122)            //полная очистка дисплея

//функции знакогенератора
void LCDG_SetInv(unsigned char flag);                                                //устанавливает флаг инверсии - текст будет белым, а фон темным 
void LCDG_SendSymbol(unsigned char xPos, unsigned char yPos, unsigned char data);   //выводит один символ в знакоместо
void LCDG_SendString(unsigned char xPos, unsigned char yPos, char * string);        //выводит строку из ОЗУ
void LCDG_SendStringFl(unsigned char xPos, unsigned char yPos, prog_char *string);  //выводит строку из флэш

//графические функции
void LCDG_SetMethod(unsigned char met);                                                 //устанавливает метод вывода пикселов на экран - И, ИЛИ, Искл ИЛИ
void LCDG_PutPixel(unsigned char XPos, unsigned char YPos);                              //отображает один пиксел на дисплее
void LCDG_DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);  //рисует линию. нужно задать 
void LCDG_DrawCircle(unsigned char x,unsigned char y,unsigned char r);                       //рисует окружность с координатами центра (x,y) 
void LCDG_DrawRect(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char fill); //рисует прямоугольник. нужно задать координаты двух вершин

#endif //LCD_GRAPH_LIB_H

