#ifndef __SENSORS_CONFIG_H
#define __SENSORS_CONFIG_H

// External sensors are connected to PC2-PC5
// If sensor is active, it drives the corresponding pin low.

#define SENSOR0_PIN (2)
#define SENSOR1_PIN (3)
#define SENSOR2_PIN (4)
#define SENSOR3_PIN (5)

#define sensors_read()    (PINC & (_BV(SENSOR0_PIN)|_BV(SENSOR1_PIN)|_BV(SENSOR2_PIN)|_BV(SENSOR3_PIN)))

// Configure PC2-PC5 for input
// 1. (do nothing with DDRC - input by default)
// 2. activate internal pull ups
#define sensors_init() do {\
  sbi(PORTC,SENSOR0_PIN);\
  sbi(PORTC,SENSOR1_PIN);\
  sbi(PORTC,SENSOR2_PIN);\
  sbi(PORTC,SENSOR3_PIN);\
} while(0)


#endif
