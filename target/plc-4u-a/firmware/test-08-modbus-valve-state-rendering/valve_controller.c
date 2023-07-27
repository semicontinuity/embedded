#include "valve_controller.h"


void valve_controller__run(void) {
    discrete_output__f__set(discrete_inputs__f__get());
}
