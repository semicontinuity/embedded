
/* �����:              Papandopala Papandopalavich
 * ��� �����:          Atmega16_LCD_LIB.c
 * ��� ��:			   Atmega16, Flash 16 Kbytes, SRAM 1 Kbytes, EEPROM 512 bytes.
 * �������� �������:   F_CPU 8000000 ��
 * ����:               28.06.2013 21:17:29
 * ������ ��:          ATMEL STUDIO VERSION 6.1.2562
 * FUSES:              HIGH xx, LOW xx;
 * ��������:           ��������� ���������� ��� ������ � LCD ��������� ������������� �� HD44780 
					   ������������. ������ ���������� �������� �� 4� � 8�� ������ ����� �����������
					   LCD, ������������ ������ ����� ������ �� �������*/ 

#include <inttypes.h>

//---------------------------------------------------------------------------------------------
//����  ������ ������������ 8�� ������ ����� �����������, ����� �������������� #define LCD_8BIT
//#define LCD_8BIT
//---------------------------------------------------------------------------------------------

#ifndef LCD
#define LCD

#if 1

//��������� ���� � �������� ���������� ������ ������� LCD DB0...DB7.
#define DPIN  PINB
#define DDDR  DDRB
#define DPORT PORTB
						
//����  ��      LCD   
//#define DB0	0// DB0
//#define DB1	1// DB1
//#define DB2	2// DB2	
//#define DB3	3// DB3		
#define DB4	4// DB4  
#define DB5	5// DB5
#define DB6	6// DB6
#define DB7	7// DB7 + BF ���� ��������� �������.

//��������� ���� � �������� ���������� ������ ������� E, RS, R/W.
#define CDDR  DDRD
#define CPORT PORTD

// ��������� ������ ����� ��, � ������� ���������� �������.
#define E	4	// E	 �����.
#define RW	3   // R/W   R/W=1 ������ �� LCD, R/W=0 ���������� � LCD.
#define RS	2 	// RS	 RS=0 �������� ������� � LCD, RS=1 �������� ������ � LCD.

#endif
//----------------------------------��������� ���������---------------------------------
#if 1
//���������������� �������, ��� ���������� � ���������.
void LCDinit(void);							//������������� LCD                    
void LCDcommand(uint8_t);					//�������� �������, ��������� �������  
void LCDGotoXY(uint8_t, uint8_t);			//������������� ������ � X, Y �������
void LCDdata(uint8_t);						//������� 1 ������ �� �������.
void LCDstring(char*i,uint8_t,uint8_t);		//������� ������ �� ������� � ������� x,y
void LCDstring_of_sram(uint8_t*,uint8_t,uint8_t,uint8_t);//������� ������ �� ������� � ������� x,y �� ���		
void LCDstring_of_flash(const uint8_t*,uint8_t, uint8_t);//������� ������ � ������� x,y �� �����
void LCDset(void);				//������������ ������� 5x8 �����.
void LCDblank(void);			//������� ��������� ���� �� �������
void LCDnblank(void);			//������� ������� ���� �� ������� + ���������� ������� ��������.
void LCDclear(void);			//�������� ������� �� ���� + ������ �� ������� 0,0
void LCDcursor_bl(void);		//�������� �������� ������
void LCDcursor_on(void);		//�������� �������������� ������
void LCDcursor_vi(void);		//�������� ��� �������
void LCDcursorOFF(void);		//��������� ������ (�����)
void LCDacr(void);				//C������ ������ AC ������ ����� ��������� �� n+1
void LCDacl(void);				//C������ ������ AC ������ ����� ��������� �� n-1
void LCDcursorl(void);			//�������� ������ ����� �� 1 ������
void LCDcursorr(void);			//�������� ������ ������ �� 1 ������
void LCDcursorln(uint8_t);		//�������� ������ ����� �� n ��������
void LCDcursorrn(uint8_t);		//�������� ������ ������ �� n ��������
void LCDscreenl(void);			//�������� ����� ����� �� 1 ������
void LCDscreenr(void);			//�������� ����� ������ �� 1 ������
void LCDscreenln(uint8_t);		//�������� ����� ����� �� n ��������
void LCDscreenrn(uint8_t);		//�������� ����� ������ �� n ��������
void LCDscreenL(void);			//� ������ ����� �������� ����� ����� ��������� �����
void LCDscreenR(void);			//� ������ ����� �������� ����� ����� ��������� ������
void LCDresshift(void);			//������ � ������� 0,0 + ����� ���� �������, ����������� ��������

//������������ �������.
#define LINE0 0x00
#define LINE1 0x40

#endif

#endif

/*������� ������������� ������
LCDcommand(0b00101000);//�������� 4� ������ ��������� ������/�������� � �������� 5x8 �����.
LCDcommand(0b00000001);//������� ������
LCDcommand(0b00000010);//��������� ������� � ������� 0,0 + ����� �������
LCDcommand(0b00000110);//���. ��������� �������� ������, �������� ����������� ���.
LCDcommand(0b00001100);//�������� ����������� �� ������� + ��� ����������� �������.
LCDdata('A');			//������ ������ �
LCDGotoXY(6,1);			//�������� ������ � ������� ������� ������ ������.
LCDdata('B');			//� ������ ������ �
LCDstring("Hi baby, i love you",0,0);//������ ������ "������ �����, � ���� �����" � ������� 0,0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
����� �������������� ������� LCDstring_of_sram, ����� � ��� ������ �������� �������� ����� ������
uint8_t text2[7] = {'H','I',' ','b','a','b','y'};
��� �����, ��� � ������� ���������.
uint8_t text3[7] = {"hi baby"};
����� �������� ������� ������ ���� ������ �� ���
LCDstring_of_sram(text3,7,0,1); 7-��� ������ 7 �������� � �������. 0,1 ������� ������ x y. 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
����� �������������� ������� LCDline_of_flush, ����� �� ���� ������ �������� �������� ����� ������
� ����� �� �������� ������ 0 ��������, ����� ��� ������� ������� �� ������� ��� ���� ������ ��.

const uint8_t text[] PROGMEM = {0x20,0xA8,0x70,0xB8,0xB3,0x65,0xBF,0x20,0xE3,0x65,0xBF,0xBA,
								0x61,0x21,0};//������ �����!
����� ��� ������ �� ����� ������� �� LCD ���:
LCDline_of_flush(text,0,1);//� ������� 0,1 �� ������� ��������� ������ �����!, ���� ���� LCD 
							 ������������ ������� �������.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~							 						 
*/
/*
������������� ������� ���������� ����� �������.
1.�������� �������.
2.����� VCC >=4.5V ���� �� ����� 15 ����.
3.�������� ������� 0x30 - 0b110000
4.���� �� ����� 4.1 ����
5.�������� ������� 0x30
6.���� �� ����� 100 �����
7.�������� ������� 0x30
����������� ���� �������� �������� ����������������� ��� LCD
� �������� ������� ������� � ������� ��������� �� ������ ���������.
8.����� �������� � �������� � ������� ������.

� �������� ��������� �=0, R/W=0, RS - ������������, DB0...DB7 ������� �������� (HI).
����� ��������� ������ �������� �=0, R/W=0 ������ �������������� ��� ����� � ����������� �����
���������� ������ ������� � ��.


������� ����������� ���:

int main(void)
{
	init();		//������������� ��.
	LCDinit();	//������������� LCD, ��� ������� � ������ �������, ����� ��� ���������.

	while(1)//������� ���� ���������.
	{
		
	}
}

����� �������� �������.
LCDGotoXY(3,1);
����� 3 �������� ��������� ������� � ����� ������. ���� 0, �� ��� ������ ������� � ����� ������.
����� 1 �������� ������ ������ � 0 �������.
|0,0|1,0|2,0|3,0|4,0|5,0|6,0|7,0| - ������ ������
|0,1|1,1|2,1|3,1|4,1|5,1|6,1|7,1| - ������ ������

1  0  0
1 I/D S  
I/D - �������� �������� ������, 0-���������� 1-����������
S   - ����� ����������� ������ 0 ���������� �� ����������, 1 ����������, 
      ���� I/D - 0 �� ������, ���� 1 �� �����.
LCDcommand(100) - ������� n-1, ����� �� ����������. ������� ����� ���������  <-
LCDcommand(110) - ������� n+1, ����� �� ����������. ������� ����� ���������  ->
LCDcommand(101)	- ������� n-1, ����������� ���������� ������ � ������ ����� ��������
LCDcommand(111) - ������� n+1, ����������� ���������� ����� � ������ ����� ��������
	   	   
1   0   0   0  0	   
1  S/C R/L  -  -     
S/C (screen/cursor) - 0 ���������� ������, 1 ���������� �����.
R/L (right/left)    - 0 ����� �����, 1 ����� ������. �� ���� ������� �� 1 �����

//����� ��� � ���� �� � ������� ��� ������� ������� �� ����� 40 �������� �� ����� ������ ������� �����.
LCDcursor_on();
LCDscreenL();
LCDGotoXY(39,1);
uint8_t i=0x21;
while(i<0x70)
{
	LCDdata(i);
	_delay_ms(500);
	i++;
}

//����� ��� � ���� �� � ������� ��� ������� ������� �� ����� 40 �������� �� ����� ������ ������� �����.
LCDcursor_on();
LCDscreenR();
LCDGotoXY(0,0);
uint8_t i=0x21;
while(i<0x70)
{
	LCDdata(i);
	_delay_ms(500);
	i++;
}

*/