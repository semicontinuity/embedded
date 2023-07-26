#ifndef DISCRETE_INPUTS_H
#define DISCRETE_INPUTS_H

#include <avr/io.h>


#ifndef discrete_inputs__byte0
extern uint8_t discrete_inputs__byte0;
#endif

#ifndef discrete_inputs__byte1
extern uint8_t discrete_inputs__byte1;
#endif


void discrete_inputs__run(void);

#ifdef discrete_inputs__on_input_0_changed
void discrete_inputs__on_input_0_changed(void);
#endif

#ifdef discrete_inputs__on_input_1_changed
void discrete_inputs__on_input_1_changed(void);
#endif

#ifdef discrete_inputs__on_input_2_changed
void discrete_inputs__on_input_2_changed(void);
#endif

#ifdef discrete_inputs__on_input_3_changed
void discrete_inputs__on_input_3_changed(void);
#endif

#ifdef discrete_inputs__on_input_4_changed
void discrete_inputs__on_input_4_changed(void);
#endif

#ifdef discrete_inputs__on_input_5_changed
void discrete_inputs__on_input_5_changed(void);
#endif

#ifdef discrete_inputs__on_input_6_changed
void discrete_inputs__on_input_6_changed(void);
#endif

#ifdef discrete_inputs__on_input_7_changed
void discrete_inputs__on_input_7_changed(void);
#endif

#ifdef discrete_inputs__on_input_8_changed
void discrete_inputs__on_input_8_changed(void);
#endif

#ifdef discrete_inputs__on_input_9_changed
void discrete_inputs__on_input_9_changed(void);
#endif

#ifdef discrete_inputs__on_input_a_changed
void discrete_inputs__on_input_a_changed(void);
#endif

#ifdef discrete_inputs__on_input_b_changed
void discrete_inputs__on_input_b_changed(void);
#endif

#ifdef discrete_inputs__on_input_c_changed
void discrete_inputs__on_input_c_changed(void);
#endif

#ifdef discrete_inputs__on_input_d_changed
void discrete_inputs__on_input_d_changed(void);
#endif

#ifdef discrete_inputs__on_input_e_changed
void discrete_inputs__on_input_e_changed(void);
#endif

#ifdef discrete_inputs__on_input_f_changed
void discrete_inputs__on_input_f_changed(void);
#endif

#endif
