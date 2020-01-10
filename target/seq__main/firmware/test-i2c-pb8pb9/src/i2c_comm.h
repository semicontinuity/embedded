// $Id$
/*
 * Header file for custom SEQ modifications
 *
 * ==========================================================================
 */

#ifndef _I2C_COMM_H
#define _I2C_COMM_H

/////////////////////////////////////////////////////////////////////////////
// Prototypes
/////////////////////////////////////////////////////////////////////////////

#include <mios32.h>

extern s32 I2C_Comm_Init(u32 mode);
extern s32 I2C_Comm_Idle(void);
extern s32 I2C_Comm_Send(u8 board);


#endif
