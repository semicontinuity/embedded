// based on messung.c

#include "temperature.h"
#include <avr/pgmspace.h>
#include "1-wire/ds18x20.h"

//#define MES_DEBUG	usart_write 
#define MES_DEBUG(...)	



volatile int16_t ow_array[MAXSENSORS];

const PROGMEM	uint8_t	DS18B20IDs[MAXSENSORS][OW_ROMCODE_SIZE] = OW_IDS;


void temperature_init(void)
{
    // For all: set 12-bit Resolution, Alarm_low_T=0, Alarm_high_T=85
//    DS18X20_write_scratchpad(0, 0, 85, DS18B20_12_BIT);
}


uint8_t start_OW(void) {
#if OW_EXTERN_POWERED
	if ( DS18X20_start_meas( DS18X20_POWER_EXTERN, 0) == DS18X20_OK ) {
	        // wait 750ms (?) for conversion
		return (DS18B20_TCONV_12BIT / TIMERBASE);
	}

	MES_DEBUG("\r\nOW short?");
	return 0;
#else
	return 1;  // wait min time(?) (well, conversion is not started!)
#endif
}


void lese_Temperatur(void) {
	uint16_t TWert;
	uint8_t subzero, cel, cel_frac_bits;
	uint8_t tempID[OW_ROMCODE_SIZE];

        uint8_t sp[DS18X20_SP_SIZE];

	int8_t i = MAXSENSORS;
	while (--i >= 0) {
		memcpy_P(tempID, DS18B20IDs[i], OW_ROMCODE_SIZE);

#if OW_EXTERN_POWERED
		if (DS18X20_read_scratchpad(tempID, sp) == DS18X20_OK) {
                    ow_array[i] = (*((int16_t*)sp)) << 4;
		}
		else {
			MES_DEBUG("CRC Error (lost connection?)\r\n");
			//DS18X20_show_id_uart( tempID, OW_ROMCODE_SIZE );
		}
#else
		if (DS18X20_start_meas (DS18X20_POWER_PARASITE, tempID) == DS18X20_OK) {
			if (tempID[0] == DS18B20_ID)
				_delay_ms(DS18B20_TCONV_10BIT);
			else
				_delay_ms(DS18S20_TCONV);


			if (DS18X20_read_scratchpad(tempID, sp) == DS18X20_OK) {
                            ow_array[i] = (*((int16_t*)sp)) << 4;
			}
			else {
				MES_DEBUG("\r\nCRC Error (lost connection?) ");
				//DS18X20_show_id_uart( tempID, OW_ROMCODE_SIZE );
			}
		}
		else MES_DEBUG("OW short?");
#endif
	}
}
