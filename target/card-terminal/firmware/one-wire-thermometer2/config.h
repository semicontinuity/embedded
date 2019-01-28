#ifndef _CONFIG_H_
	#define _CONFIG_H_	

//	#define F_CPU 16000000UL	
	
	#define TIMERBASE		25		//!< Zeitbasis für Timerinterrupt ist 25 ms


	#define USE_OW			1
	#define MAXSENSORS		4
	#define OW_ONE_BUS		1
									//   die Ports werden in onewire.h definiert
	#define OW_EXTERN_POWERED 1
	#define OW_ROMCODE_SIZE 8

	#define OW_ID_T01		{0x28, 0x2E, 0x29, 0xA2, 0x04, 0x00, 0x00, 0x80}
	#define OW_ID_T02		{0x28, 0xAE, 0xD7, 0xA2, 0x04, 0x00, 0x00, 0x6E}
	#define OW_ID_T03		{0x28, 0xA9, 0x39, 0xA3, 0x04, 0x00, 0x00, 0x1C}
	#define OW_ID_T04		{0x28, 0x68, 0x4E, 0xA2, 0x04, 0x00, 0x00, 0x07}

        #define OW_IDS {OW_ID_T01, OW_ID_T02, OW_ID_T03, OW_ID_T04}
#endif //_CONFIG_H
