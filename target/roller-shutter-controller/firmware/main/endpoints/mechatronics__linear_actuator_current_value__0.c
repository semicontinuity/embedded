#include "endpoints/mechatronics__linear_actuator_target_value__0.h"
#include "motor_controller.h"
#include "kernel.h"


void mechatronics__linear_actuator_current_value__0__broadcast(void) {
    kernel__send(
        (const uint8_t*)&motor_controller__status.position,
        sizeof(motor_controller__status.position),
        UCAN_CHANNEL_ID,
        0,
        UCAN__PID__MECHATRONICS__LINEAR_ACTUATOR_CURRENT_VALUE
    );
}


void mechatronics__linear_actuator_current_value__0__handle_post(void) {
    // ignore invalid frames
    motor_controller__position = (int8_t)kernel__frame.data[0];
}
