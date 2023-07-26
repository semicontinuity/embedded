#include <stdint.h>
#include "drivers/in/digital_inputs.h"

#include "drivers/in/buttons.h"
#include "drivers/in/extra_inputs.h"
#include "drivers/in/valve_limit_switches.h"
#include "drivers/in/water_leak_sensors.h"


void digital_inputs__init(void) {
    water_leak_sensor__a__init();
    water_leak_sensor__b__init();
    water_leak_sensor__c__init();
    water_leak_sensor__d__init();

    valve_limit_switch__a__init();
    valve_limit_switch__b__init();
    valve_limit_switch__c__init();
    valve_limit_switch__d__init();

    extra_input__a__init();
    extra_input__b__init();

    button__a__init();
    button__b__init();
    button__c__init();
    button__d__init();
    button__e__init();
    button__f__init();
}
