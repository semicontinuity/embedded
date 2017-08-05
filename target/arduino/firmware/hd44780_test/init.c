
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~������������� �� � ���������~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <avr/io.h> 
#include <inttypes.h>
#include <avr/interrupt.h>
#include "LCD.h"      //����� ��� LCD �������

#include "cpu/avr/gpio.h"

void init(void)
{
	
	#if 1    /*��������� ������*/
/*
	==============================================================================================
	 ddr(x) - ������ ��� ����� �����:
	 1 - �����
	 0 - ����
	==============================================================================================
	 port(x) - �������� �������� �����:
	 1 - �������� ��������
	 0 - �������� ���������
	 �������� 0 ��� �� ������������� ����� � 0 ��� ��������� ���-��, ����
	 ����� ��������������� �������, � 1 �������� ����� ������������ ������ �������
	==============================================================================================*/
								/*��������� ������*/
	
//	DDRA  = 0b11111111;			//���� 0 ������ ����
//	PORTA = 0b00000000;			//���� 1 �������� ��������

//	DDRB  = 0b11111111;
//	PORTB = 0b00000000;

//	DDRC  = 0b11111111;
//	PORTC = 0b00000000;

//	DDRD  = 0b11111111;
//	PORTD = 0b00000000;

        USE_AS_OUTPUT(LCD__D4);
        USE_AS_OUTPUT(LCD__D5);
        USE_AS_OUTPUT(LCD__D6);
        USE_AS_OUTPUT(LCD__D7);
        USE_AS_OUTPUT(LCD__RES);
        USE_AS_OUTPUT(LCD__RW);
        USE_AS_OUTPUT(LCD__E);
    #endif
	
	//==============================================================================================
	                   
	#if 0	 /*��������� ������� TCNT0*/
	
	TCCR0=(0<<FOC0)|(0<<WGM00)|(0<<COM01)|(0<<COM00)|(0<<WGM01)|(0<<CS02)|(0<<CS01)|(1<<CS00);
	  /* CS02...CS00 - ��������� ������������.
		 000-������ ����, 001-1, 010-8, 011 - 64, 100 - 256, 101 - 1024*/
	  	
	TIMSK|=(1<<OCIE0)|(0<<TOIE0);	//��������� ���������� ����������
	  /*
		���0 ����. ����. �� ������������ �������� ��������                   �0 (TOIE0)
		���1 ����. ����. �� ���������� �������� ���������� � ��������� ����� �0 (OCIE0)
		���2 ����. ����. �� ������������ �������� ��������                   �1 (TOIE1)
		���3 ����. ����. �� ���������� �������� ���������� � ��������� ����� �1 (OCIE1B)
		���4 ����. ����. �� ���������� �������� ���������� � ��������� ����� �1 (OCIE1A)
		���5 ����. ����. �� �������                                          �1 (TICIE1)
		���6 ����. ����. �� ������������ �������� ��������                   �2 (TOIE2)
		���7 ����. ����. �� ���������� �������� ���������� � ��������� ����� �2 (OCIE2) */
	  
	SFIOR|=(0<<PSR10);//����� ������������ �0,�1 ���. ��������.
	OCR0=1;

	#endif
	
    //==============================================================================================
	LCDinit();
	//sei();
}
     