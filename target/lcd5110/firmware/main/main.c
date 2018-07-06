//Atmega8A - ������������ ���������������
//#define F_CPU 8000000
#include <util/delay.h>
#include <stdlib.h>
//#include 
//�������  ����������
#include "n5110.h"
 
int main(void)
{
//�������������� �������
Lcd_init();
//������� ����������
float f_data = 14.43; //�������
int i_data = 123; //�����
char s_data[5] = "Hello"; //������
    while(1)
    {
        //�������� ��������� 
        //������� �������
        Lcd_clear();
        //Lcd_prints ��� ������ ��������� ������
        Lcd_prints(0, 0, FONT_1X,(unsigned char *)PSTR("������!"));
        //Lcd_print ��� ������ �� ����������
        Lcd_print(0, 1, FONT_1X,(unsigned char *)s_data);
        //Lcd_printf ��� ������ �������� ����� (�������������� float � string)
        //2 - ����� ������ ����� �������
        Lcd_printf(0, 2, FONT_1X, f_data, 2);
        //��� ������ ����� ����������� ��� � ������ ��� ������ ���������� 
        //������� itoa(�����, ������,������� ���������)
        char buff[20];
        itoa(i_data, buff, 10);
        Lcd_print(0, 3, FONT_1X,(unsigned char *)buff);
        //��������� ������  
        Lcd_update();
        //�������� 2 �������
        _delay_ms(2000);
        //������� �������
        Lcd_clear();
        //�������� ������
        for (int i=0;i<=10;i++)
        {
            Lcd_circle(40, 24, i, PIXEL_ON);
        }
        //��������� ������
        Lcd_update();
        //�������� 2 �������
        _delay_ms(2000);
    }
}