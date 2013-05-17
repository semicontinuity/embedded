//***************************************************************************
//
//  Author(s)...: Pashgan    http://ChipEnable.Ru   
//
//  Target(s)...: ����� ����
//
//  Compiler....: IAR EWA 5.11A
//
//  Description.: ������� ������������ ���������� ��12232
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
//  ������������ ���������
//
//������� ������������ ��
#ifndef F_CPU
  #define F_CPU 16000000
#endif

//���� � �������� ���������� ����������� �������
#define PORT_LCD_CON PORTD
#define PIN_LCD_CON  PIND
#define DDRX_LCD_CON DDRD

//���� � �������� ���������� ���� ������ 
#define PORT_LCD_BUS PORTB  
#define PIN_LCD_BUS  PINB
#define DDRX_LCD_BUS DDRB

//���� � �������� ��������� EN
#define PORT_LCD_EN  PORTC  
#define PIN_LCD_EN   PINC
#define DDRX_LCD_EN  DDRC

//���� � �������� ��������� RES
#define PORT_LCD_RES PORTC  
#define PIN_LCD_RES  PINC
#define DDRX_LCD_RES DDRC

//������ � ������� ���������� ����������� ������� ���
#define RES     1
#define CS      1
#define AO      4
#define RD_WR   5
#define EN      2

//*****************************************************************************
//
//  ����������������
//
//�������
#define COM_DISPLAY_ON       0xaf               //�������� ���
#define COM_DISPLAY_OFF      0xae               //��������� ���
#define COM_START_LINE(x)    (0xc0&(0x1f&(x)))  //���������� ������� ������ ���
#define COM_ADC_SELECT_OFF   0xa0               //������ ������������ ������ � �������
#define COM_ADC_SELECT_ON    0xa1               //�������� ������������ ������ � �������
#define COM_STATIC_DRIVE_ON  0xa5               //����������� ����� ����������
#define COM_STATIC_DRIVE_OFF 0xa4               //������� ����������
#define COM_DUTY_SELECT_ON   0xa9               //����� ������������
#define COM_CLEAR_RMW        0xee               //������ ����� RMW
#define COM_SELECT_RMW       0xe0               //��������� ����� RMW
#define COM_RESET            0xe2               //������ � �������� ������������ � 0

//������ ������ �� �����
#define MET_AND  0
#define MET_OR   1
#define MET_XOR  2

#define FILL_OFF 0  //���������� ���
#define FILL_ON  1  //���������� ����

//******************************************************************************
//
//  �������
//
//�������������� �������
unsigned char LCDG_ReadData(void);                       //������ ����� ���. ����� �������������� ����� ���������� ����� �������� � �������
void LCDG_SendCom(unsigned char data);                   //������ �������
void LCDG_SendData(unsigned char data);                  //������ ������

//������� �������������
extern void LCDG_InitPort(void);                                //������������� ����� �����������
void LCDG_InitLcd(void);                                 //������������� lcd. ������ ����������������� ������ ��� ����� ������������ ������ 
void LCDG_ClrDisp(unsigned char x1, unsigned char x2);   //������� ������� �� x1 �� x2
#define LCDG_ClrAllDisp() LCDG_ClrDisp(0, 122)            //������ ������� �������

//������� ���������������
void LCDG_SetInv(unsigned char flag);                                                //������������� ���� �������� - ����� ����� �����, � ��� ������ 
void LCDG_SendSymbol(unsigned char xPos, unsigned char yPos, unsigned char data);   //������� ���� ������ � ����������
void LCDG_SendString(unsigned char xPos, unsigned char yPos, char * string);        //������� ������ �� ���
void LCDG_SendStringFl(unsigned char xPos, unsigned char yPos, prog_char *string);  //������� ������ �� ����

//����������� �������
void LCDG_SetMethod(unsigned char met);                                                 //������������� ����� ������ �������� �� ����� - �, ���, ���� ���
void LCDG_PutPixel(unsigned char XPos, unsigned char YPos);                              //���������� ���� ������ �� �������
void LCDG_DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);  //������ �����. ����� ������ 
void LCDG_DrawCircle(unsigned char x,unsigned char y,unsigned char r);                       //������ ���������� � ������������ ������ (x,y) 
void LCDG_DrawRect(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char fill); //������ �������������. ����� ������ ���������� ���� ������

#endif //LCD_GRAPH_LIB_H

