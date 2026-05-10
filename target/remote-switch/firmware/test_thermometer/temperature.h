#ifndef __TEMPERATURE_H
#define __TEMPERATURE_H

#include <stdint.h>
//#include "config.h"


extern volatile int16_t ow_array[MAXSENSORS];	// Speicherplatz für 1-wire Sensorwerte

void temperature_init(void);
uint8_t start_OW(void);
uint8_t lese_Temperatur(void);

#endif
