#include <stdint.h>

#include "temperature.h"
#include "1-wire/ds18x20.h"
#include "1-wire/onewire.h"

#include <string.h>
#include <stdio.h>


uint8_t id[OW_ROMCODE_SIZE];

uint8_t start_OW(void) {
#if OW_EXTERN_POWERED
	if ( DS18X20_start_meas( DS18X20_POWER_EXTERN, 0) == DS18X20_OK ) {
	        // wait 750ms (?) for conversion
		return (DS18B20_TCONV_12BIT / TIMERBASE);
	}

//	MES_DEBUG("\r\nOW short?");
	return 0;
#else
	return 1;  // wait min time(?) (well, conversion is not started!)
#endif
}


void temperature_init(void)
{
    ow_reset();
    
    uint8_t diff = OW_SEARCH_FIRST;
    
    while(diff != OW_LAST_DEVICE) {
        DS18X20_find_sensor(&diff, id);
        
        if( diff == OW_PRESENCE_ERR ) {
//            debug('E', "no sensor");
            break;
        }

        if( diff == OW_DATA_ERR ) {
//            debug('E', "bus error");
            break;
        }
        
//        debug('I', "sensor id %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x", id[0], id[1], id[2], id[3], id[4], id[5], id[6], id[7]);
    }
}
