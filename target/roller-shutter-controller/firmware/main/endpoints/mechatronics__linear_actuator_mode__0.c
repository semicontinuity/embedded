#include "endpoints/mechatronics__linear_actuator_mode__0.h"
#include "motor_controller.h"
#include "kernel.h"


void mechatronics__linear_actuator_mode__0__broadcast(void) {
    kernel__send(
        (const uint8_t*)&motor_controller__motor_mode,
        sizeof(motor_controller__motor_mode),
        UCAN_CHANNEL_ID,
        0,
        UCAN__PID__MECHATRONICS__LINEAR_ACTUATOR_MODE
    );
}


void mechatronics__linear_actuator_mode__0__handle_post(void) {
    const motor_controller__motor_mode_t *motor_mode_ptr = (const motor_controller__motor_mode_t *)&kernel__frame.data;
    const motor_controller__motor_mode_t motor_mode = *motor_mode_ptr;

    if (motor_mode == MOTOR_CONTROLLER__MOTOR_MODE__STOPPED) {
        motor_controller__stop();
    }
    else if (motor_mode == MOTOR_CONTROLLER__MOTOR_MODE__RUNNING_UP) {
        motor_controller__move_up();
    }
    else if (motor_mode == MOTOR_CONTROLLER__MOTOR_MODE__RUNNING_DOWN) {
        motor_controller__move_down();
    }
    // ignore invalid values
}
