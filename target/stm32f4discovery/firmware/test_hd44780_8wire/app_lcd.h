#ifndef _APP_LCD_H
#define _APP_LCD_H

#ifdef __cplusplus
extern "C" {
#endif

typedef signed int s32;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

extern s32 APP_LCD_Init(u32 mode);
extern s32 APP_LCD_Data(u8 data);
extern s32 APP_LCD_Cmd(u8 cmd);
extern s32 APP_LCD_Clear(void);
extern s32 APP_LCD_CursorSet(u16 column, u16 line);
extern s32 APP_LCD_SpecialCharInit(u8 num, u8 table[8]);

/////////////////////////////////////////////////////////////////////////////
// Export global variables
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif /* _APP_LCD_H */
