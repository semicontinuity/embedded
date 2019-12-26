// $Id$
/*
 * Header file for custom SEQ modifications
 *
 * ==========================================================================
 */

#ifndef _SEQ_MOD_H
#define _SEQ_MOD_H

/////////////////////////////////////////////////////////////////////////////
// Prototypes
/////////////////////////////////////////////////////////////////////////////

extern s32 SEQ_Mod_Init(u32 mode);
extern s32 SEQ_Mod_Idle(void);
extern s32 SEQ_Mod_TerminalParseLine(char *input, void *_output_function);


#endif /* _SEQ_MOD_H */
