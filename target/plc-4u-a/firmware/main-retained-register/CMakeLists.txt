cmake_minimum_required(VERSION 3.11)
project(main-retained-register)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)


set(SOURCE_FILES
        ../../../../cpu/avr/asm.h
        ../../../../cpu/avr/macros.h
        ../../../../cpu/avr/asm_bit_var.h

        ../../../../cpu/avr/timer0.h
        ../../../../cpu/avr/timer0.c
        ../../../../cpu/avr/timer1.h
        ../../../../cpu/avr/timer1.c
        ../../../../cpu/avr/timer2.h
        ../../../../cpu/avr/timer2.c

        ../../../../cpu/avr/drivers/comm/modbus/buffer.h
        ../../../../cpu/avr/drivers/comm/modbus/buffer.c
        ../../../../cpu/avr/drivers/comm/modbus/modbus.h
        ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver.h
        ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver.c
        ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__delay_timer.h
        ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__delay_timer.c
        ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__dir_control.h
        ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__dir_control__nop.c
        ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__usart_rx.h
        ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__usart_rx.c
        ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__usart_tx.h
        ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__usart_tx.c
        ../../../../cpu/avr/drivers/comm/modbus/modbus_server.h
        ../../../../cpu/avr/drivers/comm/modbus/modbus_server.c

        ../../bsp/drivers/in/digital_inputs.h
        ../../bsp/drivers/in/digital_inputs.c
        ../../bsp/drivers/out/digital_outputs.h
        ../../bsp/drivers/out/buzzer.h
        ../../bsp/drivers/buzzer_timer.h
        ../../bsp/drivers/buzzer_timer.c
        ../../bsp/drivers/fast_timer.h
        ../../bsp/drivers/fast_timer.c

        ../../bsp/services/discrete_inputs.h
        ../../bsp/services/discrete_inputs.c
        ../../bsp/services/coils.h
        ../../bsp/services/coils.c
        ../../bsp/services/holding_registers.h
        ../../bsp/services/holding_registers.c
        ../../bsp/services/retained_registers.h
        ../../bsp/services/retained_registers.c

        ../../bsp/services/slow_timer.h
        ../../bsp/services/slow_timer.c
        ../../bsp/services/seconds_timer.h
        ../../bsp/services/seconds_timer.c
        ../../bsp/services/uptime_counter.h
        ../../bsp/services/uptime_counter.c
        ../../bsp/services/basic_rtc.h
        ../../bsp/services/basic_rtc.c

        valve_controller__1.h
        valve_controller__1.c
        contactor_controller.h
        contactor_controller.c
        alert_controller.h
        alert_controller.c
        water_leak_sensors_controller.h
        water_leak_sensors_controller.c
        buzzer_control.h
        buzzer_control.c

        comm__modbus__callbacks.c
        comm__modbus__coils.c
        comm__modbus__holding_registers.c
        comm__modbus__discrete_inputs.c

        main.c

        __all__.c
)

include_directories(. ../../bsp ../../../../ /opt/arduino-1.8.19/hardware/tools/avr/avr/include)
add_executable(main ${SOURCE_FILES})

include(CMakeLists.config.txt)
