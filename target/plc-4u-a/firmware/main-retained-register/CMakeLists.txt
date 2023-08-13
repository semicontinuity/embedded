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
#        ../../../../cpu/avr/timer2.h
#        ../../../../cpu/avr/timer2.c

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
        ../../bsp/drivers/fast_timer.h
        ../../bsp/drivers/fast_timer.c

        ../../bsp/services/discrete_inputs.h
        ../../bsp/services/discrete_inputs.c
        ../../bsp/services/discrete_outputs.h
        ../../bsp/services/discrete_outputs.c
        ../../bsp/services/internal_coils.h
        ../../bsp/services/internal_coils.c
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
        contactor_control.h
        contactor_control.c
        failure_indicator.h
        failure_indicator.c
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

add_definitions(-D__AVR_ATmega328P__)
add_definitions(-DINLINE=)
add_definitions(-DCRC16__TABLE2x256__SECTION=.crc16_table2x256)

add_definitions(-DF_CPU=16000000UL)

# Parameters
# ==============================================================================
add_definitions(-DUSART0__BAUD_RATE=4800)
add_definitions(-DBUZZER__TIMEOUT=240)


# Outputs
# ==============================================================================
# (from WATER_LEAK_SENSOR C,D)
add_definitions(-DVALVE_CONTROL__A__PWR__PORT=D)
add_definitions(-DVALVE_CONTROL__A__PWR__PIN=4)
add_definitions(-DVALVE_CONTROL__A__DIR__PORT=D)
add_definitions(-DVALVE_CONTROL__A__DIR__PIN=5)

# (dummy, unused in atmega328p)
add_definitions(-DVALVE_CONTROL__B__PWR__PORT=D)
add_definitions(-DVALVE_CONTROL__B__PWR__PIN=4)
add_definitions(-DVALVE_CONTROL__B__DIR__PORT=D)
add_definitions(-DVALVE_CONTROL__B__DIR__PIN=5)

# (from VALVE_LIMIT_SWITCH C,D)
add_definitions(-DEXTRA_OUTPUT__A__PORT=B)
add_definitions(-DEXTRA_OUTPUT__A__PIN=0)
add_definitions(-DEXTRA_OUTPUT__B__PORT=B)
add_definitions(-DEXTRA_OUTPUT__B__PIN=1)

# (from BUTTON C,D)
add_definitions(-DBUTTON_LED__A__PORT=C)
add_definitions(-DBUTTON_LED__A__PIN=2)
add_definitions(-DBUTTON_LED__B__PORT=C)
add_definitions(-DBUTTON_LED__B__PIN=3)

# (dummy, unused in atmega328p)
add_definitions(-DBUTTON_LED__C__PORT=C)
add_definitions(-DBUTTON_LED__C__PIN=2)
add_definitions(-DBUTTON_LED__D__PORT=C)
add_definitions(-DBUTTON_LED__D__PIN=3)

# (CONTACTOR: from extra input C, ALARM: onboard LED)
add_definitions(-DBUTTON_LED__E__PORT=B)
add_definitions(-DBUTTON_LED__E__PIN=4)
add_definitions(-DBUTTON_LED__F__PORT=B)
add_definitions(-DBUTTON_LED__F__PIN=5)

# (Same as Button LED F = Failure LED, which is not driven yet)
add_definitions(-DBUZZER__PORT=B)
add_definitions(-DBUZZER__PIN=5)

# Digital inputs
# ==============================================================================

# Water leak sensor A
add_definitions(-DDIGITAL_INPUTS__0__PORT=D)
add_definitions(-DDIGITAL_INPUTS__0__PIN=2)

# Water leak sensor B
add_definitions(-DDIGITAL_INPUTS__1__PORT=D)
add_definitions(-DDIGITAL_INPUTS__1__PIN=3)

# Water leak sensor C
add_definitions(-DDIGITAL_INPUTS__2__PORT=D)
add_definitions(-DDIGITAL_INPUTS__2__PIN=4)

# Water leak sensor D
add_definitions(-DDIGITAL_INPUTS__3__PORT=D)
add_definitions(-DDIGITAL_INPUTS__3__PIN=5)

# Valve limit switch A
add_definitions(-DDIGITAL_INPUTS__4__PORT=D)
add_definitions(-DDIGITAL_INPUTS__4__PIN=6)

# Valve limit switch B
add_definitions(-DDIGITAL_INPUTS__5__PORT=D)
add_definitions(-DDIGITAL_INPUTS__5__PIN=7)

# Valve limit switch C
add_definitions(-DDIGITAL_INPUTS__6__PORT=B)
add_definitions(-DDIGITAL_INPUTS__6__PIN=0)

# Valve limit switch D
add_definitions(-DDIGITAL_INPUTS__7__PORT=B)
add_definitions(-DDIGITAL_INPUTS__7__PIN=1)

# Extra Input A
add_definitions(-DDIGITAL_INPUTS__8__PORT=B)
add_definitions(-DDIGITAL_INPUTS__8__PIN=2)

# Extra Input B
add_definitions(-DDIGITAL_INPUTS__9__PORT=B)
add_definitions(-DDIGITAL_INPUTS__9__PIN=3)

# Button A
add_definitions(-DDIGITAL_INPUTS__A__PORT=C)
add_definitions(-DDIGITAL_INPUTS__A__PIN=0)

# Button B
add_definitions(-DDIGITAL_INPUTS__B__PORT=C)
add_definitions(-DDIGITAL_INPUTS__B__PIN=1)

# Button C
add_definitions(-DDIGITAL_INPUTS__C__PORT=C)
add_definitions(-DDIGITAL_INPUTS__C__PIN=2)

# Button D
add_definitions(-DDIGITAL_INPUTS__D__PORT=C)
add_definitions(-DDIGITAL_INPUTS__D__PIN=3)

# Button E
add_definitions(-DDIGITAL_INPUTS__E__PORT=C)
add_definitions(-DDIGITAL_INPUTS__E__PIN=4)

# Button F
add_definitions(-DDIGITAL_INPUTS__F__PORT=C)
add_definitions(-DDIGITAL_INPUTS__F__PIN=5)

# Digital inputs
# ==============================================================================

add_definitions(-DWATER_LEAK_SENSOR__A__PORT=D)
add_definitions(-DWATER_LEAK_SENSOR__A__PIN=2)
add_definitions(-DWATER_LEAK_SENSOR__B__PORT=D)
add_definitions(-DWATER_LEAK_SENSOR__B__PIN=3)

# (dummy, unused in atmega328p)
add_definitions(-DWATER_LEAK_SENSOR__C__PORT=D)
add_definitions(-DWATER_LEAK_SENSOR__C__PIN=4)
add_definitions(-DWATER_LEAK_SENSOR__D__PORT=D)
add_definitions(-DWATER_LEAK_SENSOR__D__PIN=5)

add_definitions(-DVALVE_LIMIT_SWITCH__A__PORT=D)
add_definitions(-DVALVE_LIMIT_SWITCH__A__PIN=6)
add_definitions(-DVALVE_LIMIT_SWITCH__B__PORT=D)
add_definitions(-DVALVE_LIMIT_SWITCH__B__PIN=7)

# (dummy, unused in atmega328p)
add_definitions(-DVALVE_LIMIT_SWITCH__C__PORT=B)
add_definitions(-DVALVE_LIMIT_SWITCH__C__PIN=0)
add_definitions(-DVALVE_LIMIT_SWITCH__D__PORT=B)
add_definitions(-DVALVE_LIMIT_SWITCH__D__PIN=1)

add_definitions(-DEXTRA_INPUT__A__PORT=B)
add_definitions(-DEXTRA_INPUT__A__PIN=2)
add_definitions(-DEXTRA_INPUT__B__PORT=B)
add_definitions(-DEXTRA_INPUT__B__PIN=3)

# (dummy, unused in atmega328p)
#add_definitions(-DEXTRA_INPUT__C__PORT=B)
#add_definitions(-DEXTRA_INPUT__C__PIN=4)

add_definitions(-DBUTTON__A__PORT=C)
add_definitions(-DBUTTON__A__PIN=0)
add_definitions(-DBUTTON__B__PORT=C)
add_definitions(-DBUTTON__B__PIN=1)

# (dummy, unused in atmega328p)
add_definitions(-DBUTTON__C__PORT=C)
add_definitions(-DBUTTON__C__PIN=2)
add_definitions(-DBUTTON__D__PORT=C)
add_definitions(-DBUTTON__D__PIN=3)

add_definitions(-DBUTTON__E__PORT=C)
add_definitions(-DBUTTON__E__PIN=4)
add_definitions(-DBUTTON__F__PORT=C)
add_definitions(-DBUTTON__F__PIN=5)

# Modbus RTU driver
# ==============================================================================

add_definitions(-DBUFFER__SIZE=256)

add_definitions(-Dmodbus_rtu_driver__frame_received__get\(\)=BITVAR_GET\(PORTB,6\))
add_definitions(-Dmodbus_rtu_driver__frame_received__set\(v\)=BITVAR_SET\(PORTB,6,v\))
add_definitions(-DMODBUS_RTU_DRIVER__FRAME_RECEIVED__LED__PORT=B)
add_definitions(-DMODBUS_RTU_DRIVER__FRAME_RECEIVED__LED__PIN=6)

add_definitions(-DMODBUS_RTU_DRIVER__USART_RX__ENABLED__HOST=PORTB)
add_definitions(-DMODBUS_RTU_DRIVER__USART_RX__ENABLED__BIT=7)
add_definitions(-DMODBUS_RTU_DRIVER__USART_RX__ENABLED__LED__PORT=B)
add_definitions(-DMODBUS_RTU_DRIVER__USART_RX__ENABLED__LED__PIN=7)

add_definitions(-DMODBUS_RTU_DRIVER__FRAME_PROCESSING__LED__PORT=C)
add_definitions(-DMODBUS_RTU_DRIVER__FRAME_PROCESSING__LED__PIN=6)

add_definitions(-DMODBUS_RTU_DRIVER__DELAY_TIMER__CONF=TIMER1_CONF_NO_PRESCALER)
add_definitions(-DMODBUS_RTU_DRIVER__DELAY_TIMER__T15_VALUE=\(\(F_CPU/USART0__BAUD_RATE\)*15\))
add_definitions(-DMODBUS_RTU_DRIVER__DELAY_TIMER__T35_VALUE=\(\(F_CPU/USART0__BAUD_RATE\)*35\))

# Modbus server
# ==============================================================================

add_definitions(-DMODBUS_SERVER__ADDRESS=2)

add_definitions(-DMODBUS_SERVER__DISCRETE_INPUTS_ADDRESSES_START=0)
add_definitions(-DMODBUS_SERVER__DISCRETE_INPUTS_COUNT=16)
add_definitions(-DMODBUS_SERVER__HANDLE_READ_DISCRETE_INPUTS=1)

add_definitions(-DMODBUS_SERVER__COIL_ADDRESSES_START=0)
add_definitions(-DMODBUS_SERVER__COIL_COUNT=32)
add_definitions(-DMODBUS_SERVER__HANDLE_READ_COILS=1)
add_definitions(-DMODBUS_SERVER__HANDLE_WRITE_SINGLE_COIL=1)

add_definitions(-DMODBUS_SERVER__HOLDING_REGISTERS_START=0)
add_definitions(-DMODBUS_SERVER__HOLDING_REGISTERS_COUNT=7)
add_definitions(-DMODBUS_SERVER__HANDLE_READ_HOLDING_REGISTERS=1)
add_definitions(-DMODBUS_SERVER__HANDLE_WRITE_REGISTER=1)

add_definitions(-DHOLDING_REGISTER__ADDRESS__BASIC_RTC__DOW_HH=0)
add_definitions(-DHOLDING_REGISTER__ADDRESS__BASIC_RTC__MM_SS=1)
add_definitions(-DHOLDING_REGISTER__ADDRESS__UPTIME__HOURS=2)
add_definitions(-DHOLDING_REGISTER__ADDRESS__UPTIME__SECONDS=3)
add_definitions(-DHOLDING_REGISTER__ADDRESS__MODBUS__DEVICE_ADDRESS=4)
add_definitions(-DHOLDING_REGISTER__ADDRESS__MODBUS__PORT_SPEED=5)
add_definitions(-DHOLDING_REGISTER__ADDRESS__REBOOT=6)



# Discrete inputs
# ==============================================================================

add_definitions(-DDEBOUNCE_TIMEOUT_MS=50)
#add_definitions(-Ddiscrete_inputs__byte0=GPIOR0)
#add_definitions(-Ddiscrete_inputs__byte1=GPIOR1)

# Discrete outputs
# ==============================================================================
#add_definitions(-Ddiscrete_outputs__byte0=OCR0B)
#add_definitions(-Ddiscrete_outputs__byte1=GPIOR2)

# Internal coils
# ==============================================================================
#add_definitions(-Dinternal_coils__byte0=SPDR)

# Valve controller
# ==============================================================================
add_definitions(-Ddiscrete_inputs__on_input_a_changed=valve_controller__1__button__open__changed)
add_definitions(-Dvalve_controller__1__button__open__get=discrete_inputs__a__get)

add_definitions(-Ddiscrete_inputs__on_input_b_changed=valve_controller__1__button__close__changed)
add_definitions(-Dvalve_controller__1__button__close__get=discrete_inputs__b__get)

add_definitions(-Ddiscrete_inputs__on_input_8_changed=contactor_control__button__changed)
add_definitions(-Dcontactor_control__button__get=discrete_inputs__8__get)

add_definitions(-Ddiscrete_inputs__on_input_f_changed=failure_indicator__button__changed)
add_definitions(-Dfailure_indicator__button__get=discrete_inputs__f__get)

add_definitions(-Dfailure_indicator__led__set=discrete_output__f__set)
