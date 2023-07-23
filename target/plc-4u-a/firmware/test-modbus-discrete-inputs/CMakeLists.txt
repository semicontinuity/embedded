cmake_minimum_required(VERSION 3.11)
project(test-modbus-discrete-inputs)

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

        discrete_inputs_debouncer.h
        discrete_inputs_debouncer.c
        fast_timer.h
        fast_timer.c
        main.c
        __all__.c
)

include_directories(. ../../bsp ../../../../ /opt/arduino-1.8.19/hardware/tools/avr/avr/include)
add_executable(main ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega328P__)
add_definitions(-DINLINE=)
add_definitions(-DCRC16__TABLE2x256__SECTION=.crc16_table2x256)

add_definitions(-DF_CPU=16000000UL)

add_definitions(-DUSART0__BAUD_RATE=4800)

add_definitions(-DWATER_LEAK_SENSOR__A__PORT=D)
add_definitions(-DWATER_LEAK_SENSOR__A__PIN=2)
add_definitions(-DWATER_LEAK_SENSOR__B__PORT=D)
add_definitions(-DWATER_LEAK_SENSOR__B__PIN=3)
add_definitions(-DWATER_LEAK_SENSOR__C__PORT=D)
add_definitions(-DWATER_LEAK_SENSOR__C__PIN=4)
add_definitions(-DWATER_LEAK_SENSOR__D__PORT=D)
add_definitions(-DWATER_LEAK_SENSOR__D__PIN=5)

add_definitions(-DVALVE_LIMIT_SWITCH__A__PORT=D)
add_definitions(-DVALVE_LIMIT_SWITCH__A__PIN=6)
add_definitions(-DVALVE_LIMIT_SWITCH__B__PORT=D)
add_definitions(-DVALVE_LIMIT_SWITCH__B__PIN=7)
add_definitions(-DVALVE_LIMIT_SWITCH__C__PORT=B)
add_definitions(-DVALVE_LIMIT_SWITCH__C__PIN=0)
add_definitions(-DVALVE_LIMIT_SWITCH__D__PORT=B)
add_definitions(-DVALVE_LIMIT_SWITCH__D__PIN=1)

add_definitions(-DEXTRA_INPUT__A__PORT=B)
add_definitions(-DEXTRA_INPUT__A__PIN=2)
add_definitions(-DEXTRA_INPUT__B__PORT=B)
add_definitions(-DEXTRA_INPUT__B__PIN=3)
add_definitions(-DEXTRA_INPUT__C__PORT=B)
add_definitions(-DEXTRA_INPUT__C__PIN=4)

add_definitions(-DBUTTON__A__PORT=C)
add_definitions(-DBUTTON__A__PIN=0)
add_definitions(-DBUTTON__B__PORT=C)
add_definitions(-DBUTTON__B__PIN=1)
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
add_definitions(-DMODBUS_SERVER__HANDLE_READ_DISCRETE_INPUTS=1)
add_definitions(-DMODBUS_SERVER__DISCRETE_INPUTS_ADDRESSES_START=0)
add_definitions(-DMODBUS_SERVER__DISCRETE_INPUTS_COUNT=16)
