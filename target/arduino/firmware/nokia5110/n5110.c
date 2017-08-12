/*
 * ��������     :  ��� ������� ��� ������������ LCD �� Nokia 5110, � ����� ��� ��������� ������.
 * �����        :  Xander Gresolio <xugres@gmail.com>
 * ���-�������� :  https://github.com/gresolio/N3310Lib
 * ��������     :  GPL v3.0
 *
 * �����������  : kobzar aka kobraz ��� http://cxem.net/ maodzedun@gmail.com
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "n5110.h"

//������ � float
int gpow(int n, int power) {
	int res = 1;
	while(power--) res *= n;
	return res;
}

/*
 * ���                   :  gftoa
 * ��������              :  ��������� float � string
 * ��������(�)           :  n - �����, power -  ����� ������ ����� �������
 * ������������ �������� :  string
 */

char *gftoa(float f, int dec) {
	static char buf[16];
	char *p = buf + 15;
	int i = f * gpow(10, dec);
	int sign = i < 0 ? -1 : 1;
	i *= sign;
	do {
		*--p = '0' + (i % 10);
		i /= 10;
		if (--dec == 0) *--p = '.';
	}
	while (i != 0);

	if (dec > 0) {
		while (dec-- > 0)
		*--p = '0';
		*--p = '.';
	}
	
	if (*p == '.') *--p = '0';

	if (sign < 0) *--p = '-';

	return p;
}

// ��������� ��������� ������� ��������

static void LcdSend    ( byte data, LcdCmdData cd );
static void Delay      ( void );

// ���������� ����������

// ��� � ��� 84*48 ��� ��� 504 �����
static byte  LcdCache [ LCD_CACHE_SIZE ];

// ����� �� ��������� ���� �������, � ���� �� ����� ��� ����������,
// ����� �������� ��� ������� ���� ��� ��������� ���������. �����
// ����� ���������� ��� ����� ���� ����� ��������� � ��� �������.
static int   LoWaterMark;   // ������ �������
static int   HiWaterMark;   // ������� �������

// ��������� ��� ������ � LcdCache[]
static int   LcdCacheIdx;

// ���� ��������� ����
static byte  UpdateLcd;


/*
 * ���                   :  Lcd_init
 * ��������              :  ���������� ������������� ����� � SPI ��, ����������� LCD
 * ��������(�)           :  ���
 * ������������ �������� :  ���
 */
void Lcd_init ( void )
{
    // Pull-up �� ����� ������������ � reset �������
    LCD_PORT |= _BV ( LCD_RST_PIN );

    // ������������� ������ ���� ����� �� �����
    LCD_DDR |= _BV( LCD_RST_PIN ) | _BV( LCD_DC_PIN ) | _BV( LCD_CE_PIN ) | _BV( SPI_MOSI_PIN ) | _BV( SPI_CLK_PIN );

    // ��������������� ��������
    Delay();

    // ������� reset
    LCD_PORT &= ~( _BV( LCD_RST_PIN ) );
    Delay();
    LCD_PORT |= _BV ( LCD_RST_PIN );

    // ���������� SPI:
    // ��� ����������, ������� ��� ������, ����� �������, CPOL->0, CPHA->0, Clk/4
    SPCR = 0x50;

    // ��������� LCD ���������� - ������� ������� �� SCE
    LCD_PORT |= _BV( LCD_CE_PIN );

    // ���������� ������� �������
    LcdSend( 0x21, LCD_CMD ); // �������� ����������� ����� ������ (LCD Extended Commands)
    LcdSend( 0xC8, LCD_CMD ); // ��������� ������������� (LCD Vop)
    LcdSend( 0x06, LCD_CMD ); // ��������� �������������� ������������ (Temp coefficent)
    LcdSend( 0x13, LCD_CMD ); // ��������� ������� (LCD bias mode 1:48)
    LcdSend( 0x20, LCD_CMD ); // �������� ����������� ����� ������ � �������������� ��������� (LCD Standard Commands,Horizontal addressing mode)
    LcdSend( 0x0C, LCD_CMD ); // ���������� ����� (LCD in normal mode)

    // ��������� ������� �������
    Lcd_clear();
    Lcd_update();
}


/*
 * ���                   :  Lcd_clear
 * ��������              :  ������� �������. ����� ���������� ��������� LcdUpdate
 * ��������(�)           :  ���
 * ������������ �������� :  ���
 */
void Lcd_clear ( void )
{

    memset( LcdCache, 0x00, LCD_CACHE_SIZE );
    
    // ����� ���������� ������ � ������������ ��������
    LoWaterMark = 0;
    HiWaterMark = LCD_CACHE_SIZE - 1;

    // ��������� ����� ��������� ����
    UpdateLcd = TRUE;
}



/*
 * ���                   :  Lcd_update
 * ��������              :  �������� ��� � ��� �������
 * ��������(�)           :  ���
 * ������������ �������� :  ���
 */
void Lcd_update (void)
{
    int i;

    if ( LoWaterMark < 0 )
        LoWaterMark = 0;
    else if ( LoWaterMark >= LCD_CACHE_SIZE )
        LoWaterMark = LCD_CACHE_SIZE - 1;

    if ( HiWaterMark < 0 )
        HiWaterMark = 0;
    else if ( HiWaterMark >= LCD_CACHE_SIZE )
        HiWaterMark = LCD_CACHE_SIZE - 1;

    #ifdef CHINA_LCD  // �������� ��� ���������� �� �� ������������� ������������

        byte x,y;

        // 102 x 64 - ������ �������������� ���������� ������ ���������� ��, ��� ���
        // ������ ������ ������������ �� ������� �� ������� ����� �� 3 �������.
        // ������� ������� �������� ���� - ������� � ������ ������ y+1, � �����
        // ������� ����� (����� ���� ���� �������, �������� � ������ ������)
                
        x = LoWaterMark % LCD_X_RES;      // ������������� ��������� ����� x
        LcdSend( 0x80 | x, LCD_CMD );     // ������������ ������ ������� LoWaterMark
        
        y = LoWaterMark / LCD_X_RES + 1;  // ������������� ��������� ����� y+1
        LcdSend( 0x40 | y, LCD_CMD );     // ������������ ������ ������� LoWaterMark

        for ( i = LoWaterMark; i <= HiWaterMark; i++ )
        {
            // �������� ������ � ����� �������
            LcdSend( LcdCache[i], LCD_DATA );
            
            x++;                 // ������ ������������ ���������� x, ����� ������� ������� �� ����� ������
            if (x >= LCD_X_RES)  // ���� ����� �� ������, �� ��������� �� ��������� ������ (x=0; y++)
            {
                // ����� ������, ����� ����� ��������� ������ ����� �������������� ������,
                // �������� ���� ��������� ��������� �����, ����� ��� �������� :)
                x=0;                
                LcdSend( 0x80, LCD_CMD );
                y++;
                LcdSend( 0x40 | y, LCD_CMD );
            }
        }

        LcdSend( 0x21, LCD_CMD );    // �������� ����������� ����� ������
        LcdSend( 0x45, LCD_CMD );    // �������� �������� �� 5 �������� ����� (������������� ������� �������, �������� � ����������)
        LcdSend( 0x20, LCD_CMD );    // �������� ����������� ����� ������ � �������������� ���������

    #else  // �������� ��� ������������� �������

        // ������������� ��������� ����� � ������������ � LoWaterMark
        LcdSend( 0x80 | ( LoWaterMark % LCD_X_RES ), LCD_CMD );
        LcdSend( 0x40 | ( LoWaterMark / LCD_X_RES ), LCD_CMD );

        // ��������� ����������� ����� ������ �������
        for ( i = LoWaterMark; i <= HiWaterMark; i++ )
        {
            // ��� ������������� ������� �� ����� ������� �� ������� � ������,
            // ����� ������ ��������������� �������� ������
            LcdSend( LcdCache[i], LCD_DATA );
        }

    #endif

    // ����� ���������� ������ � �������
    LoWaterMark = LCD_CACHE_SIZE - 1;
    HiWaterMark = 0;

    // ����� ����� ��������� ����
    UpdateLcd = FALSE;
}


/*
 * ���                   :  LcdSend
 * ��������              :  ���������� ������ � ���������� �������
 * ��������(�)           :  data -> ������ ��� ��������
 *                          cd   -> ������� ��� ������ (������ enum � n5110.h)
 * ������������ �������� :  ���
 */
static void LcdSend ( byte data, LcdCmdData cd )
{
    // �������� ���������� ������� (������ ������� ��������)
    LCD_PORT &= ~( _BV( LCD_CE_PIN ) );

    if ( cd == LCD_DATA )
    {
        LCD_PORT |= _BV( LCD_DC_PIN );
    }
    else
    {
        LCD_PORT &= ~( _BV( LCD_DC_PIN ) );
    }

    // �������� ������ � ���������� �������
    SPDR = data;

    // ���� ��������� ��������
    while ( (SPSR & 0x80) != 0x80 );

    // ��������� ���������� �������
    LCD_PORT |= _BV( LCD_CE_PIN );
}


/*
 * ���                   :  LcdContrast
 * ��������              :  ������������� ������������� �������
 * ��������(�)           :  �������� -> �������� �� 0x00 � 0x7F
 * ������������ �������� :  ���
 */
void LcdContrast ( byte contrast )
{
    LcdSend( 0x21, LCD_CMD );              // ����������� ����� ������
    LcdSend( 0x80 | contrast, LCD_CMD );   // ��������� ������ �������������
    LcdSend( 0x20, LCD_CMD );              // ����������� ����� ������, �������������� ���������
}


/*
 * ���                   :  Delay
 * ��������              :  ��������������� �������� ��� ��������� ������������� LCD
 * ��������(�)           :  ���
 * ������������ �������� :  ���
 */
static void Delay ( void )
{
    int i;

    for ( i = -32000; i < 32000; i++ );
}


/*
 * ���                   :  LcdGotoXY
 * ��������              :  ������������� ������ � ������� x,y ������������ ������������ ������� ������
 * ��������(�)           :  x,y -> ���������� ����� ������� �������. ��������: 0,0 .. 13,5
 * ������������ �������� :  ������ ������������ �������� � n5110.h
 */
byte LcdGotoXY ( byte x, byte y )
{
    // �������� ������
    if( x > 13 || y > 5 ) return OUT_OF_BORDER;

    //  ���������� ���������. ��������� ��� ����� � �������� 504 ����
    LcdCacheIdx = x * 6 + y * 84;
    return OK;
}


/*
 * ���                   :  LcdChr
 * ��������              :  ������� ������ � ������� ������� �������, ����� �������������� ��������� �������
 * ��������(�)           :  size -> ������ ������. ������ enum � n5110.h
 *                          ch   -> ������ ��� ������
 * ������������ �������� :  ������ ������������ �������� � n5110lcd.h
 */
byte LcdChr ( LcdFontSize size, byte ch )
{
    byte i, c;
    byte b1, b2;
    int  tmpIdx;

    if ( LcdCacheIdx < LoWaterMark )
    {
        // ��������� ������ �������
        LoWaterMark = LcdCacheIdx;
    }

    if ( (ch >= 0x20) && (ch <= 0x7F) )
    {
        // �������� � ������� ��� �������� ASCII[0x20-0x7F]
        ch -= 32;
    }
    else if ( ch >= 0xC0 )
    {
        // �������� � ������� ��� �������� CP1251[0xC0-0xFF]
        ch -= 96;
    }
    else
    {
        // ��������� ���������� (�� ������ ��� � ������� ��� �������� ������)
        ch = 95;
    }

    if ( size == FONT_1X )
    {
        for ( i = 0; i < 5; i++ )
        {
            // �������� ��� ������� �� ������� � ���
            LcdCache[LcdCacheIdx++] = pgm_read_byte( &(FontLookup[ch][i]) ) << 1;
        }
    }
    else if ( size == FONT_2X )
    {
        tmpIdx = LcdCacheIdx - 84;

        if ( tmpIdx < LoWaterMark )
        {
            LoWaterMark = tmpIdx;
        }

        if ( tmpIdx < 0 ) return OUT_OF_BORDER;

        for ( i = 0; i < 5; i++ )
        {
            // �������� ��� ������� �� ������� � ��������� ����������
            c = pgm_read_byte(&(FontLookup[ch][i])) << 1;
            // ����������� ��������
            // ������ �����
            b1 =  (c & 0x01) * 3;
            b1 |= (c & 0x02) * 6;
            b1 |= (c & 0x04) * 12;
            b1 |= (c & 0x08) * 24;

            c >>= 4;
            // ������ �����
            b2 =  (c & 0x01) * 3;
            b2 |= (c & 0x02) * 6;
            b2 |= (c & 0x04) * 12;
            b2 |= (c & 0x08) * 24;

            // �������� ��� ����� � ���
            LcdCache[tmpIdx++] = b1;
            LcdCache[tmpIdx++] = b1;
            LcdCache[tmpIdx + 82] = b2;
            LcdCache[tmpIdx + 83] = b2;
        }

        // ��������� x ���������� �������
        LcdCacheIdx = (LcdCacheIdx + 11) % LCD_CACHE_SIZE;
    }

    if ( LcdCacheIdx > HiWaterMark )
    {
        // ��������� ������� �������
        HiWaterMark = LcdCacheIdx;
    }

    // �������������� ������ ����� ���������
    LcdCache[LcdCacheIdx] = 0x00;
    // ���� �������� ������� ��������� LCD_CACHE_SIZE - 1, ��������� � ������
    if(LcdCacheIdx == (LCD_CACHE_SIZE - 1) )
    {
        LcdCacheIdx = 0;
        return OK_WITH_WRAP;
    }
    // ����� ������ �������������� ���������
    LcdCacheIdx++;
    return OK;
}


/*
 * ���                   :  Lcd_print
 * ��������              :  ��� ������� ������������� ��� ������ ������ �� ����������
 * ��������(�)           :  size      -> ������ ������. ������ enum � n5110.h
 *                       :  dataArray -> ������ ���������� ������ ������� ����� ����������
 *						 :  x,y -> ����������
 * ������������ �������� :  ������ ������������ �������� � n5110lcd.h
 * ������                :  LcdFStr(0, 0, FONT_1X,(unsigned char*)some_char);
 *                          LcdFStr(0, 0, FONT_1X, &name_of_string_as_array);
 */
byte Lcd_print ( byte x, byte y, LcdFontSize size, byte dataArray[] )
{
	LcdGotoXY(x,y);
    byte tmpIdx=0;
    byte response;
    while( dataArray[ tmpIdx ] != '\0' )
    {
        // ������� ������
        response = LcdChr( size, dataArray[ tmpIdx ] );
        // �� ����� ����������� ���� ���������� OUT_OF_BORDER,
        // ������ ����� ���������� ������ �� ������ �������
        if( response == OUT_OF_BORDER)
            return OUT_OF_BORDER;
        // ����������� ���������
        tmpIdx++;
    }
    return OK;
}



/*
 * ���                   :  Lcd_prints
 * ��������              :  ��� ������� ������������� ��� ������ ��������� ������ 
 * ��������(�)           :  size    -> ������ ������. ������ enum � n5110.h
 *                          dataPtr -> ��������� �� ������ ������� ����� ����������
 *						 :  x,y -> ����������
 * ������������ �������� :  ������ ������������ �������� � n5110lcd.h
 * ������                :  LcdFStr(0, 0, FONT_1X, PSTR("Hello World"));
 *                          LcdFStr(0, 0, FONT_1X, &name_of_string_as_array);
 */
byte Lcd_prints ( byte x, byte y, LcdFontSize size, const byte *dataPtr )
{
    LcdGotoXY(x,y);
	byte c;
    byte response;
    for ( c = pgm_read_byte( dataPtr ); c; ++dataPtr, c = pgm_read_byte( dataPtr ) )
    {
        // ������� ������
        response = LcdChr( size, c );
        if(response == OUT_OF_BORDER)
            return OUT_OF_BORDER;
    }

    return OK;
}


/*
 * ���                   :  Lcd_printf
 * ��������              :  ��� ������� ������������� ��� ������ ����� � ��������� �������
 * ��������(�)           :  size      -> ������ ������. ������ enum � n5110.h
 *                       :  data -> �����
 *						 :	accuracy -> ����� ������ ����� �������
 *						 :  x,y -> ����������
 * ������������ �������� :  ������ ������������ �������� � n5110lcd.h
 * ������                :  LcdFStr(0, 0, FONT_1X, float_var , 2);
 *                          LcdFStr(0, 0, FONT_1X, &name_of_string_as_array);
 */
void Lcd_printf ( byte x, byte y, LcdFontSize size, float data, int accuracy )
{
	Lcd_print(x, y, size, (unsigned char*)gftoa(data, accuracy));
}



/*
 * ���                   :  Lcd_pixel
 * ��������              :  ���������� ������� �� ���������� ����������� (x,y)
 * ��������(�)           :  x,y  -> ���������� ���������� �������
 *                          mode -> Off, On ��� Xor. ������ enum � n5110.h
 * ������������ �������� :  ������ ������������ �������� � n5110lcd.h
 */
byte Lcd_pixel ( byte x, byte y, LcdPixelMode mode )
{
    int  index;
    byte  offset;
    byte  data;

    // ������ �� ������ �� �������
    if ( x >= LCD_X_RES || y >= LCD_Y_RES) return OUT_OF_BORDER;

    // �������� ������� � ��������
    index = ( ( y / 8 ) * 84 ) + x;
    offset  = y - ( ( y / 8 ) * 8 );

    data = LcdCache[ index ];

    // ��������� �����

    // ����� PIXEL_OFF
    if ( mode == PIXEL_OFF )
    {
        data &= ( ~( 0x01 << offset ) );
    }
    // ����� PIXEL_ON
    else if ( mode == PIXEL_ON )
    {
        data |= ( 0x01 << offset );
    }
    // ����� PIXEL_XOR
    else if ( mode  == PIXEL_XOR )
    {
        data ^= ( 0x01 << offset );
    }

    // ������������� ��������� �������� � ���
    LcdCache[ index ] = data;

    if ( index < LoWaterMark )
    {
        // ��������� ������ �������
        LoWaterMark = index;
    }

    if ( index > HiWaterMark )
    {
        // ��������� ������� �������
        HiWaterMark = index;
    }
    return OK;
}



/*
 * ���                   :  Lcd_line
 * ��������              :  ������ ����� ����� ����� ������� �� ������� (�������� ����������)
 * ��������(�)           :  x1, y1  -> ���������� ���������� ������ �����
 *                          x2, y2  -> ���������� ���������� ����� �����
 *                          mode    -> Off, On ��� Xor. ������ enum � n5110.h
 * ������������ �������� :  ������ ������������ �������� � n5110lcd.h
 */
byte Lcd_line ( byte x1, byte y1, byte x2, byte y2, LcdPixelMode mode )
{
    int dx, dy, stepx, stepy, fraction;
    byte response;

    // dy   y2 - y1
    // -- = -------
    // dx   x2 - x1

    dy = y2 - y1;
    dx = x2 - x1;

    // dy �������������
    if ( dy < 0 )
    {
        dy    = -dy;
        stepy = -1;
    }
    else
    {
        stepy = 1;
    }

    // dx �������������
    if ( dx < 0 )
    {
        dx    = -dx;
        stepx = -1;
    }
    else
    {
        stepx = 1;
    }

    dx <<= 1;
    dy <<= 1;

    // ������ ��������� �����
    response = Lcd_pixel( x1, y1, mode );
    if(response)
        return response;

    // ������ ��������� ����� �� �����
    if ( dx > dy )
    {
        fraction = dy - ( dx >> 1);
        while ( x1 != x2 )
        {
            if ( fraction >= 0 )
            {
                y1 += stepy;
                fraction -= dx;
            }
            x1 += stepx;
            fraction += dy;

            response = Lcd_pixel( x1, y1, mode );
            if(response)
                return response;

        }
    }
    else
    {
        fraction = dx - ( dy >> 1);
        while ( y1 != y2 )
        {
            if ( fraction >= 0 )
            {
                x1 += stepx;
                fraction -= dy;
            }
            y1 += stepy;
            fraction += dx;

            response = Lcd_pixel( x1, y1, mode );
            if(response)
                return response;
        }
    }

    // ��������� ����� ��������� ����
    UpdateLcd = TRUE;
    return OK;
}



/*
 * ���                   :  Lcd_circle
 * ��������              :  ������ ���������� (�������� ����������)
 * ��������(�)           :  x, y   -> ���������� ���������� ������
 *                          radius -> ������ ����������
 *                          mode   -> Off, On ��� Xor. ������ enum � n5110.h
 * ������������ �������� :  ������ ������������ �������� � n5110lcd.h
 */
byte Lcd_circle(byte x, byte y, byte radius, LcdPixelMode mode)
{
    signed char xc = 0;
    signed char yc = 0;
    signed char p = 0;

    if ( x >= LCD_X_RES || y >= LCD_Y_RES) return OUT_OF_BORDER;

    yc = radius;
    p = 3 - (radius<<1);
    while (xc <= yc)  
    {
        Lcd_pixel(x + xc, y + yc, mode);
        Lcd_pixel(x + xc, y - yc, mode);
        Lcd_pixel(x - xc, y + yc, mode);
        Lcd_pixel(x - xc, y - yc, mode);
        Lcd_pixel(x + yc, y + xc, mode);
        Lcd_pixel(x + yc, y - xc, mode);
        Lcd_pixel(x - yc, y + xc, mode);
        Lcd_pixel(x - yc, y - xc, mode);
        if (p < 0) p += (xc++ << 2) + 6;
            else p += ((xc++ - yc--)<<2) + 10;
    }

    // ��������� ����� ��������� ����
    UpdateLcd = TRUE;
    return OK;
}


/*
 * ���                   :  Lcd_rect  (rectangle)
 * ��������              :  ������ ���� ����������� �������������
 * ��������(�)           :  baseX  -> ���������� ���������� x (������ ����� ����)
 *                          baseY  -> ���������� ���������� y (������ ����� ����)
 *                          height -> ������ (� ��������)
 *                          width  -> ������ (� ��������)
 *                          mode   -> Off, On ��� Xor. ������ enum � n5110.h
 * ������������ �������� :  ������ ������������ �������� � n5110lcd.h
 */
byte Lcd_rect ( byte baseX, byte baseY, byte height, byte width, LcdPixelMode mode )
{
    byte tmpIdxX,tmpIdxY,tmp;

    byte response;

    // �������� ������
    if ( ( baseX >= LCD_X_RES) || ( baseY >= LCD_Y_RES) ) return OUT_OF_BORDER;

    if ( height > baseY )
        tmp = 0;
    else
        tmp = baseY - height + 1;

    // ��������� �����
    for ( tmpIdxY = tmp; tmpIdxY <= baseY; tmpIdxY++ )
    {
        for ( tmpIdxX = baseX; tmpIdxX < (baseX + width); tmpIdxX++ )
        {
            response = Lcd_pixel( tmpIdxX, tmpIdxY, mode );
            if(response)
                return response;

        }
    }

    // ��������� ����� ��������� ����
    UpdateLcd = TRUE;
    return OK;
}






/*
 * ���                   :  Lcd_rect_empty
 * ��������              :  ������ ������������� �������������
 * ��������(�)           :  x1    -> ���������� ���������� x ������ �������� ����
 *                          y1    -> ���������� ���������� y ������ �������� ����
 *                          x2    -> ���������� ���������� x ������� ������� ����
 *                          y2    -> ���������� ���������� y ������� ������� ����
 *                          mode  -> Off, On ��� Xor. ������ enum � n5110.h
 * ������������ �������� :  ������ ������������ �������� � n5110lcd.h
 */
byte Lcd_rect_empty ( byte x1, byte y1, byte x2, byte y2, LcdPixelMode mode )
{
    byte tmpIdx;

    // �������� ������
    if ( ( x1 >= LCD_X_RES) ||  ( x2 >= LCD_X_RES) || ( y1 >= LCD_Y_RES) || ( y2 >= LCD_Y_RES) )
        return OUT_OF_BORDER;

    if ( ( x2 > x1 ) && ( y2 > y1 ) )
    {
        // ������ �������������� �����
        for ( tmpIdx = x1; tmpIdx <= x2; tmpIdx++ )
        {
            Lcd_pixel( tmpIdx, y1, mode );
            Lcd_pixel( tmpIdx, y2, mode );
        }

        // ������ ������������ �����
        for ( tmpIdx = y1; tmpIdx <= y2; tmpIdx++ )
        {
            Lcd_pixel( x1, tmpIdx, mode );
            Lcd_pixel( x2, tmpIdx, mode );
        }

        // ��������� ����� ��������� ����
        UpdateLcd = TRUE;
    }
    return OK;
}

