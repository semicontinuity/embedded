#include "endpoints/mechatronics__linear_actuator_target_value__0.h"
#include "motor_controller.h"
#include "kernel.h"


void mechatronics__linear_actuator_target_value__0__broadcast(void) {
    kernel__send(
        (const uint8_t*)&motor_controller__control.target_position,
        sizeof(motor_controller__control.target_position),
        UCAN_CHANNEL_ID,
        0,
        UCAN__PID__MECHATRONICS__LINEAR_ACTUATOR_TARGET_VALUE
    );
}


void mechatronics__linear_actuator_target_value__0__handle_post(void) {
    const int8_t target_position = (int8_t)kernel__frame.data[0];
    if (target_position >= MOTOR_CONTROLLER__POSITION__UP && target_position <= MOTOR_CONTROLLER__POSITION__DOWN) {
        motor_controller__move(target_position);
    }
}
