#ifndef __CPU__AVR__DRIVERS__MCP251X__REGISTERS_H
#define __CPU__AVR__DRIVERS__MCP251X__REGISTERS_H

#define MCP251X_REGISTER_RXF0SIDH	(0x00)
#define MCP251X_REGISTER_RXF0SIDL	(0x01)
#define MCP251X_REGISTER_RXF0EID8	(0x02)
#define MCP251X_REGISTER_RXF0EID0	(0x03)

#define MCP251X_REGISTER_RXF1SIDH	(0x04)
#define MCP251X_REGISTER_RXF1SIDL	(0x05)
#define MCP251X_REGISTER_RXF1EID8	(0x06)
#define MCP251X_REGISTER_RXF1EID0	(0x07)

#define MCP251X_REGISTER_RXF2SIDH	(0x08)
#define MCP251X_REGISTER_RXF2SIDL	(0x09)
#define MCP251X_REGISTER_RXF2EID8	(0x0A)
#define MCP251X_REGISTER_RXF2EID0	(0x0B)

#define MCP251X_REGISTER_BFPCTRL	(0x0C)
#define MCP251X_REGISTER_TXRTSCTRL	(0x0D)
#define MCP251X_REGISTER_CANSTAT	(0x0E)
#define MCP251X_REGISTER_CANCTRL	(0x0F)

#define MCP251X_REGISTER_RXF3SIDH	(0x10)
#define MCP251X_REGISTER_RXF3SIDL	(0x11)
#define MCP251X_REGISTER_RXF3EID8	(0x12)
#define MCP251X_REGISTER_RXF3EID0	(0x13)

#define MCP251X_REGISTER_RXF4SIDH	(0x14)
#define MCP251X_REGISTER_RXF4SIDL	(0x15)
#define MCP251X_REGISTER_RXF4EID8	(0x16)
#define MCP251X_REGISTER_RXF4EID0	(0x17)

#define MCP251X_REGISTER_RXF5SIDH	(0x18)
#define MCP251X_REGISTER_RXF5SIDL	(0x19)
#define MCP251X_REGISTER_RXF5EID8	(0x1A)
#define MCP251X_REGISTER_RXF5EID0	(0x1B)

#define MCP251X_REGISTER_TEC		(0x1C)
#define MCP251X_REGISTER_REC		(0x1D)

#define MCP251X_REGISTER_RXM0SIDH	(0x20)
#define MCP251X_REGISTER_RXM0SIDL	(0x21)
#define MCP251X_REGISTER_RXM0EID8	(0x22)
#define MCP251X_REGISTER_RXM0EID0	(0x23)

#define MCP251X_REGISTER_RXM1SIDH	(0x24)
#define MCP251X_REGISTER_RXM1SIDL	(0x25)
#define MCP251X_REGISTER_RXM1EID8	(0x26)
#define MCP251X_REGISTER_RXM1EID0	(0x27)

#define MCP251X_REGISTER_CNF3		(0x28)
#define MCP251X_REGISTER_CNF2		(0x29)
#define MCP251X_REGISTER_CNF1		(0x2A)
#define MCP251X_REGISTER_CANINTE	(0x2B)
#define MCP251X_REGISTER_CANINTF	(0x2C)
#define MCP251X_REGISTER_EFLG		(0x2D)

#define MCP251X_REGISTER_TXB0CTRL	(0x30)
#define MCP251X_REGISTER_TXB0SIDH	(0x31)
#define MCP251X_REGISTER_TXB0SIDL	(0x32)
#define MCP251X_REGISTER_TXB0EID8	(0x33)
#define MCP251X_REGISTER_TXB0EID0	(0x34)
#define MCP251X_REGISTER_TXB0DLC	(0x35)
#define MCP251X_REGISTER_TXB0D0		(0x36)
#define MCP251X_REGISTER_TXB0D1		(0x37)
#define MCP251X_REGISTER_TXB0D2		(0x38)
#define MCP251X_REGISTER_TXB0D3		(0x39)
#define MCP251X_REGISTER_TXB0D4		(0x3A)
#define MCP251X_REGISTER_TXB0D5		(0x3B)
#define MCP251X_REGISTER_TXB0D6		(0x3C)
#define MCP251X_REGISTER_TXB0D7		(0x3D)

#define MCP251X_REGISTER_TXB1CTRL	(0x40)
#define MCP251X_REGISTER_TXB1SIDH	(0x41)
#define MCP251X_REGISTER_TXB1SIDL	(0x42)
#define MCP251X_REGISTER_TXB1EID8	(0x43)
#define MCP251X_REGISTER_TXB1EID0	(0x44)
#define MCP251X_REGISTER_TXB1DLC	(0x45)
#define MCP251X_REGISTER_TXB1D0		(0x46)
#define MCP251X_REGISTER_TXB1D1		(0x47)
#define MCP251X_REGISTER_TXB1D2		(0x48)
#define MCP251X_REGISTER_TXB1D3		(0x49)
#define MCP251X_REGISTER_TXB1D4		(0x4A)
#define MCP251X_REGISTER_TXB1D5		(0x4B)
#define MCP251X_REGISTER_TXB1D6		(0x4C)
#define MCP251X_REGISTER_TXB1D7		(0x4D)

#define MCP251X_REGISTER_TXB2CTRL	(0x50)
#define MCP251X_REGISTER_TXB2SIDH	(0x51)
#define MCP251X_REGISTER_TXB2SIDL	(0x52)
#define MCP251X_REGISTER_TXB2EID8	(0x53)
#define MCP251X_REGISTER_TXB2EID0	(0x54)
#define MCP251X_REGISTER_TXB2DLC	(0x55)
#define MCP251X_REGISTER_TXB2D0		(0x56)
#define MCP251X_REGISTER_TXB2D1		(0x57)
#define MCP251X_REGISTER_TXB2D2		(0x58)
#define MCP251X_REGISTER_TXB2D3		(0x59)
#define MCP251X_REGISTER_TXB2D4		(0x5A)
#define MCP251X_REGISTER_TXB2D5		(0x5B)
#define MCP251X_REGISTER_TXB2D6		(0x5C)
#define MCP251X_REGISTER_TXB2D7		(0x5D)

#define MCP251X_REGISTER_RXB0CTRL	(0x60)
#define MCP251X_REGISTER_RXB0SIDH	(0x61)
#define MCP251X_REGISTER_RXB0SIDL	(0x62)
#define MCP251X_REGISTER_RXB0EID8	(0x63)
#define MCP251X_REGISTER_RXB0EID0	(0x64)
#define MCP251X_REGISTER_RXB0DLC	(0x65)
#define MCP251X_REGISTER_RXB0D0		(0x66)
#define MCP251X_REGISTER_RXB0D1		(0x67)
#define MCP251X_REGISTER_RXB0D2		(0x68)
#define MCP251X_REGISTER_RXB0D3		(0x69)
#define MCP251X_REGISTER_RXB0D4		(0x6A)
#define MCP251X_REGISTER_RXB0D5		(0x6B)
#define MCP251X_REGISTER_RXB0D6		(0x6C)
#define MCP251X_REGISTER_RXB0D7		(0x6D)

#define MCP251X_REGISTER_RXB1CTRL	(0x70)
#define MCP251X_REGISTER_RXB1SIDH	(0x71)
#define MCP251X_REGISTER_RXB1SIDL	(0x72)
#define MCP251X_REGISTER_RXB1EID8	(0x73)
#define MCP251X_REGISTER_RXB1EID0	(0x74)
#define MCP251X_REGISTER_RXB1DLC	(0x75)
#define MCP251X_REGISTER_RXB1D0		(0x76)
#define MCP251X_REGISTER_RXB1D1		(0x77)
#define MCP251X_REGISTER_RXB1D2		(0x78)
#define MCP251X_REGISTER_RXB1D3		(0x79)
#define MCP251X_REGISTER_RXB1D4		(0x7A)
#define MCP251X_REGISTER_RXB1D5		(0x7B)
#define MCP251X_REGISTER_RXB1D6		(0x7C)
#define MCP251X_REGISTER_RXB1D7		(0x7D)

#endif