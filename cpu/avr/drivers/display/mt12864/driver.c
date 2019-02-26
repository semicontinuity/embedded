// Source code adopted from electronix.ru
// --------------------------------------

#include "cpu/avr/drivers/display/mt12864/driver.h"

#include <stdint.h>
#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <avr/pgmspace.h>


#define SMALL_DELAY (F_CPU/1000000)
#define LARGE_DELAY (F_CPU/100000)


/*--------------------------------------------------------------------------------------------*/
/* ��������� �������� ���������� ����������� ���.                                             */
/* ���������:   ���������� (0, 1).                                                            */
/* ����������:  true, ���� ���������� �����, false �����.                                     */
/*--------------------------------------------------------------------------------------------*/
uint8_t Wait_LCD_Ready(uint8_t c)
{
  register uint8_t i = 0;
  // ��������� ���� ������ �� ���� � �������� ��� ����������� �������.
  LCD_Data_Bus_To_Input();
  mt12864_set_line_RW;
  mt12864_clear_line_E;
  mt12864_clear_line_A0;
  mt12864_clear_cs(c);
  // ���������� ����� � ������� � ���� ������ ��������� �����������.
  for(i = 0; i < 10; i++)
     {
       _delay_loop_1(SMALL_DELAY);
       mt12864_set_line_E;
       _delay_loop_1(SMALL_DELAY);
       register uint8_t state = Get_Data_from_LCD_Data_Bus();
       mt12864_clear_line_E;
       if((state & _BV(7)) == 0) break;
     }
  // ������ ������� � ���.
  mt12864_set_cs;
  return i < 10;
}

/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ ������� � ����������� ���.                                                */
/* ���������:   ���������� (0, 1), ��� ������������ �������.                                  */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
void Write_Cmd_to_LCD(uint8_t c, uint8_t cmd)
{
  // �������� ���������� ����������� ���.
  Wait_LCD_Ready(c);
  // ��������� ���� ������ �� ����� � �������� ��� ����������� �������.
  LCD_Data_Bus_to_Output();
  mt12864_clear_line_E;
  mt12864_clear_line_A0;
  mt12864_clear_line_RW;
  mt12864_clear_cs (c);

  // �������� �� ���� ������ ��� ������� � ���������� ��� �������.
  Put_Data_to_LCD_Data_Bus(cmd);
  mt12864_set_line_E;
  _delay_loop_1(SMALL_DELAY);
  mt12864_clear_line_E;
  // ������ ������� � ���.
  mt12864_set_cs;
}



/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ 1 ����� ������ � ���������� ���.                                          */
/* ���������:   ���������� (0, 1), ������������ ���� ������.                                  */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
void Write_Data_to_LCD(uint8_t c, uint8_t data)
{
  // �������� ���������� ����������� ���.
  Wait_LCD_Ready(c);
  // ��������� ���� ������ �� ����� � �������� ��� ����������� �������.
  LCD_Data_Bus_to_Output();
  mt12864_set_line_A0;
  mt12864_clear_line_E;
  mt12864_clear_line_RW;
  mt12864_clear_cs(c);
  // �������� �� ���� ������ ���� ������ � ���������� ��� �������.
  Put_Data_to_LCD_Data_Bus(data);
  mt12864_set_line_E;
  _delay_loop_1(SMALL_DELAY);
  mt12864_clear_line_E;
  // ������ ������� � ���.
  mt12864_set_cs;
}

/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ n ������ ������ � ���������� ���.                                         */
/* ���������:   ���������� (0, 1), ����� ������� ��������� ������, ����� ��������� ������.    */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/

void Write_Data_to_LCD_prog(uint8_t c, uint8_t * pData , uint8_t n)
{
  // �������� ���������� ����������� ���.
  Wait_LCD_Ready(c);
  // ��������� ���� ������ �� ����� � �������� ��� ����������� �������.
  LCD_Data_Bus_to_Output();
  mt12864_set_line_A0;
  mt12864_clear_line_E;
  mt12864_clear_line_RW;
  mt12864_clear_cs(c);
  // � ����� ��c������� �� ���� ������ ����� � ������������ �� ��������.
  for(register uint8_t i = 0; i < n; i++)
     {
       Put_Data_to_LCD_Data_Bus(*(pData + i));
       mt12864_set_line_E;
       _delay_loop_1(SMALL_DELAY);
       mt12864_clear_line_E;
       _delay_loop_1(LARGE_DELAY);
     }
  // ������ ������� � ���.
  mt12864_set_cs;
}


/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ n ������ ������ � ���������� ���.                                         */
/* ���������:   ���������� (0, 1), ����� ������� ��������� ������, ����� ��������� ������.    */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
/*
void Write_Data_to_LCD(uint8_t c, uint8_t* pData, uint8_t n)
{
  // �������� ���������� ����������� ���.
  Wait_LCD_Ready(c);
  // ��������� ���� ������ �� ����� � �������� ��� ����������� �������.
  LCD_Data_Bus_to_Output();
  mt12864_set_line_A0;
  mt12864_clear_line_E;
  mt12864_clear_line_RW;
  mt12864_clear_cs(c);
  // � ����� ��c������� �� ���� ������ ����� � ������������ �� ��������.
  for(register uint8_t i = 0; i < n; i++)
     {
       Put_Data_to_LCD_Data_Bus(*(pData + i));
       mt12864_set_line_E;
       _delay_loop_1(SMALL_DELAY);
       mt12864_clear_line_E;
       _delay_loop_1(LARGE_DELAY);
     }
  // ������ ������� � ���.
  mt12864_set_cs;
}
*/

/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ n ����� ����� ������ � ���������� ���.                                    */
/* ���������:   ���������� (0, 1), ��������� ����, ����� ��� ����������.                      */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
void Write_Data_to_LCD_n(uint8_t c, uint8_t data, uint8_t n)
{
  // �������� ���������� ����������� ���.
  Wait_LCD_Ready(c);
  // ��������� ���� ������ �� ����� � �������� ��� ����������� �������.
  LCD_Data_Bus_to_Output();
  mt12864_set_line_A0;
  mt12864_clear_line_E;
  mt12864_clear_line_RW;
  mt12864_clear_cs(c);
  // � ����� ��c������� �� ���� ������ ���� ������ � ������������ ��� �������.
  for(register uint8_t i = 0; i < n; i++)
     {
       Put_Data_to_LCD_Data_Bus(data);
       mt12864_set_line_E;
       _delay_loop_1(SMALL_DELAY);
       mt12864_clear_line_E;
       _delay_loop_1(LARGE_DELAY);
     }
  // ������ ������� � ���.
  mt12864_set_cs;
  return;
}



/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ n ������ ������ � ������� ���.                                            */
/* ���������:   ���������� ������ ������ (��������/�������),                                  */
/*              ����� ������� � ������������� �������, ����� ������������ ������.             */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
void Write_Data_to_LCD_4(uint8_t P, uint8_t C, uint8_t *pData, uint8_t n)
{
  uint8_t x = C, i = 0;
  while(x < (C + n))
    {
      if(x < 64)
        {
          Write_Cmd_Page_Addr_Set(0, P);
          Write_Cmd_Column_Addr_Set(0, x);
          i = 64 - x;
          Write_Data_to_LCD_prog(0, pData, i);
        }
      else
        {
          Write_Cmd_Page_Addr_Set(1, P);
          Write_Cmd_Column_Addr_Set(1, x - 64);
          i = (C + n) - x;
          Write_Data_to_LCD_prog(1, pData, i);
        }
      x += i;
      pData += i;
    }
}



/*--------------------------------------------------------------------------------------------*/
/* ��������� ������� ���.                                                                     */
/* ���������:   ������ �� ���������.                                                          */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
void LCD_Clear(void)
{
  for(char page = 0; page < 8; page++)
     {
       // ��������� ��������.
       Write_Cmd_Page_Addr_Set(0, page);
       Write_Cmd_Page_Addr_Set(1, page);
       // ������� ��� ������� ��������.
       Write_Cmd_Column_Addr_Set(0, 0);
       Write_Cmd_Column_Addr_Set(1, 0);
       Write_Data_to_LCD_n(0, (uint8_t)0x00, 64);
       Write_Data_to_LCD_n(1, (uint8_t)0x00, 64);
     }
  return;
}


/*--------------------------------------------------------------------------------------------*/
/* ��������� ������������� �������.                                                           */
/* ���������:   ������ �� ���������.                                                          */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
void mt12864_init(void)
{
  // ��������� � �������� ��������� ����� ���������� ���:
  // ��� ������ � ������� ���������, ������ CS1 � CS2 = "1".
  mt12864_configure_ports();
  mt12864_clear_all_control_lines();
  mt12864_set_cs;

  // ��������� ���������� ����� ������. ����� ��������� ����������, ��� ���
  // ���������� ��� ����� ���� �� ���������.
  mt12864_clear_line_RES;
  _delay_loop_2(1000);
  mt12864_set_line_RES;
  _delay_loop_2(1000);

  // ������� � �������� �������.
  LCD_Clear();
  Write_Cmd_Display_ON();
  // �������� ���������, ���� ��� ���������.
//  LCD_BackLight_ON_Cntr = 0;
//  Start_Timer(LCD_BACKLIGHT_TIMER, 1, &LCD_BackLight_Timer_Proc, TIMER_CYCLE);
}


/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ 1 ����� ������ �� ����������� ���.                                        */
/* ���������:   ���������� (0, 1).                                                            */
/* ����������:  ��������� ����.                                                               */
/*--------------------------------------------------------------------------------------------*/
uint8_t Read_Data_from_LCD_1(uint8_t c)
{
  // �������� ���������� ����������� ���.
  Wait_LCD_Ready(c);
  // ��������� ���� ������ �� ���� � �������� ��� ����������� �������.
  LCD_Data_Bus_To_Input();
  mt12864_set_line_A0;
  mt12864_set_line_RW;
  mt12864_clear_line_E;
  mt12864_clear_cs(c);
  // ������ ������ - dummy.
  mt12864_set_line_E;
  _delay_loop_1(SMALL_DELAY);
  mt12864_clear_line_E;
  _delay_loop_1(LARGE_DELAY);
  // ���������� ����� � ������� � ���� ������ ����.
  mt12864_set_line_E;
  _delay_loop_1(SMALL_DELAY);
  register uint8_t data = Get_Data_from_LCD_Data_Bus();
  mt12864_clear_line_E;
  // ������ ������� � ���.
  mt12864_set_cs;
  return data;
}

/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ n ������ ������ �� ����������� ���.                                       */
/* ���������:   ���������� (0, 1), ����� ������� ��� ��������� ������, ����� ����. ������.    */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
void Read_Data_from_LCD(uint8_t c, uint8_t *pData, uint8_t n)
{
  // �������� ���������� ����������� ���.
  Wait_LCD_Ready(c);
  // ��������� ���� ������ �� ���� � �������� ��� ����������� �������.
  LCD_Data_Bus_To_Input();
  mt12864_set_line_A0;
  mt12864_set_line_RW;
  mt12864_clear_line_E;
  mt12864_clear_cs(c);
  // ������ ������ - dummy.
  mt12864_set_line_E;
  _delay_loop_1(SMALL_DELAY);
  mt12864_clear_line_E;
  // � ����� ��������� ������ � ������� � ���� ������ �����.
  for(register uint8_t i = 0; i < n; i++)
     {
       _delay_loop_1(LARGE_DELAY);
       mt12864_set_line_E;
       _delay_loop_1(SMALL_DELAY);
       *(pData + i) = Get_Data_from_LCD_Data_Bus();
       mt12864_clear_line_E;
     }
  // ������ ������� � ���.
  mt12864_set_cs;
  return;
}

/*--------------------------------------------------------------------------------------------*/
/* ��������� ������ ����������� n �������� ���.                                               */
/* ���������:   ���������� ������ ������ (��������/�������),                                  */
/*              ����� ������� ��� ��������� ������, ����� ����������� ������.                 */
/* ����������:  ������ �� ����������.                                                         */
/*--------------------------------------------------------------------------------------------*/
void Read_Data_from_LCD_4(uint8_t P, uint8_t C, uint8_t *pData, uint8_t n)
{
  register uint8_t c = C, i = 0;
  while(c < (C + n))
    {
      if(c < 64)
        {
          Write_Cmd_Page_Addr_Set(0, P);
          Write_Cmd_Column_Addr_Set(0, c);
          i = 64 - c;
          Read_Data_from_LCD(0, pData, i);
        }
      else
        {
          Write_Cmd_Page_Addr_Set(1, P);
          Write_Cmd_Column_Addr_Set(1, c - 64);
          i = (C + n) - c;
          Read_Data_from_LCD(1, pData, i);
        }
      c += i;
      pData += i;
    }
  return;
}
