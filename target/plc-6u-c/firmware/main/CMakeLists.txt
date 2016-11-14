cmake_minimum_required(VERSION 2.8.4)
project(main)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c
    services/temperature_reader.c

    ../../bsp/drivers/comm/onewire__t0t2.c
    ../../bsp/drivers/comm/onewire__bus__noninverting_buffer.c

    ../../bsp/drivers/out/rts.h
    ../../bsp/drivers/water_counter.c
    ../../bsp/drivers/water_counter.h
    ../../../../cpu/avr/drivers/comm/modbus/buffer.c
    ../../../../cpu/avr/drivers/comm/modbus/buffer.h
    ../../../../cpu/avr/drivers/comm/modbus/modbus.h
    ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver.c
    ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver.h
    ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__delay_timer.c
    ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__delay_timer.h
    ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__dir_control.h
    ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__dir_control__nop.c
    ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__dir_control__rts.c
    ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__usart_rx.c
    ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__usart_rx.h
    ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__usart_tx.c
    ../../../../cpu/avr/drivers/comm/modbus/modbus_rtu_driver__usart_tx.h
    ../../../../cpu/avr/drivers/comm/modbus/modbus_server.c
    ../../../../cpu/avr/drivers/comm/modbus/modbus_server.h
    ../../../../cpu/avr/int1.c
    ../../../../cpu/avr/timer1.h
    ../../../../cpu/avr/timer1__2oc.h
    ../../../../cpu/avr/usart0.h
    ../../../../ ../../../../../../avrgcc/avr/include/avr/iom8535.h
)


include_directories(. ../../bsp ../../../../ ../../../../../../avrgcc/avr/include ../../../../../../avrgcc/lib/gcc/avr/4.8.1/include)
add_executable(main ${SOURCE_FILES})


add_definitions(-D__AVR_ATmega8535__)
add_definitions(-DINLINE=)
add_definitions(-DMCU=atmega8535)
add_definitions(-DOPT="2 -Wa,-a,-ad")
add_definitions(-DFIXED_REGISTERS="-ffixed-r26 -ffixed-r27 -ffixed-r28 -ffixed-r29")

# System
# ==============================================================================
add_definitions(-DF_CPU=16000000UL)


# Outputs
# ==============================================================================
add_definitions(-DOUT__RTS__PORT=D)
add_definitions(-DOUT__RTS__PIN=7)

# Inputs
# ==============================================================================
add_definitions(-DINT1__PULLUP=1)

# USART
# ==============================================================================
add_definitions(-DUSART0__BAUD_RATE=250000UL)

# Buffer
# ==============================================================================
add_definitions(-DBUFFER__SIZE=256)
add_definitions(-DBUFFER__POSITION_PTR__REG=26)
add_definitions(-DBUFFER__LIMIT_PTR__REG=28)

# Modbus RTU driver
# ==============================================================================
add_definitions(-DMODBUS_RTU_DRIVER__DELAY_TIMER__CONF=TIMER1_CONF_NO_PRESCALER)
add_definitions(-DMODBUS_RTU_DRIVER__DELAY_TIMER__T15_VALUE="\(\(F_CPU/USART0__BAUD_RATE\)*15\)")
add_definitions(-DMODBUS_RTU_DRIVER__DELAY_TIMER__T35_VALUE="\(\(F_CPU/USART0__BAUD_RATE\)*35\)")


# Modbus server
# ==============================================================================
add_definitions(-DMODBUS_SERVER__HOLDING_REGISTERS_START=0)
add_definitions(-DMODBUS_SERVER__HOLDING_REGISTERS_COUNT=5)
add_definitions(-DMODBUS_SERVER__INPUT_REGISTERS_START=0)
add_definitions(-DMODBUS_SERVER__INPUT_REGISTERS_COUNT=1)

add_definitions(-DMODBUS_SERVER__HANDLE_READ_HOLDING_REGISTERS=1)
add_definitions(-DMODBUS_SERVER__HANDLE_READ_INPUT_REGISTERS=1)
add_definitions(-DMODBUS_SERVER__HANDLE_WRITE_REGISTER=1)


# Display
# ==============================================================================
add_definitions(-DDISPLAY_DIGIT0__PORT=A)
add_definitions(-DDISPLAY_DIGIT1__PORT=C)

add_definitions(-DDISPLAY_SEGMENT_A__PIN=2)
add_definitions(-DDISPLAY_SEGMENT_B__PIN=3)
add_definitions(-DDISPLAY_SEGMENT_C__PIN=6)
add_definitions(-DDISPLAY_SEGMENT_D__PIN=5)
add_definitions(-DDISPLAY_SEGMENT_E__PIN=4)
add_definitions(-DDISPLAY_SEGMENT_F__PIN=1)
add_definitions(-DDISPLAY_SEGMENT_G__PIN=0)
add_definitions(-DDISPLAY_SEGMENT_DP__PIN=7)

# 1-Wire
# ==============================================================================
#add_definitions(-DONEWIRE__PORT=D)
#add_definitions(-DONEWIRE__PIN=7)
#add_definitions(-DONEWIRE__TIMER__FAST_CONF=TIMER2_CONF_PRESCALER_32|TIMER2_CONF_WGM_CTC)
#add_definitions(-DONEWIRE__TIMER__SLOW_CONF=TIMER2_CONF_PRESCALER_256|TIMER2_CONF_WGM_CTC)
#add_definitions(-DONEWIRE__TIMER__TIME_QUANTUM=2)

add_definitions(-DONEWIRE__OUT__PORT=D)
add_definitions(-DONEWIRE__OUT__PIN=2)
add_definitions(-DONEWIRE__IN__PORT=D)
add_definitions(-DONEWIRE__IN__PIN=5)

add_definitions(-DONEWIRE__THREAD__IP__REG=28)
add_definitions(-DONEWIRE__THREAD__BIT_COUNT__REG=16)
add_definitions(-DONEWIRE__THREAD__DATA__REG=17)

add_definitions(-DONEWIRE__BIT_SPAN_TIMER__FAST_CONF=TIMER0_CONF_PRESCALER_8|TIMER0_CONF_WGM_NORMAL)
add_definitions(-DONEWIRE__BIT_SPAN_TIMER__FAST_CONF_TIMEOUT=140)
add_definitions(-DONEWIRE__BIT_SPAN_TIMER__SLOW_CONF=TIMER0_CONF_PRESCALER_64|TIMER0_CONF_WGM_NORMAL)
add_definitions(-DONEWIRE__BIT_SPAN_TIMER__SLOW_CONF_TIMEOUT=240)
add_definitions(-DONEWIRE__BIT_FORM_TIMER__FAST_CONF=TIMER2_CONF_PRESCALER_8|TIMER2_CONF_WGM_NORMAL)
add_definitions(-DONEWIRE__BIT_FORM_TIMER__SLOW_CONF=TIMER2_CONF_PRESCALER_64|TIMER2_CONF_WGM_NORMAL)
add_definitions(-DONEWIRE__BIT_FORM_TIMER__WRITE1_DRIVE_HIGH_TIME=12)
add_definitions(-DONEWIRE__BIT_FORM_TIMER__WRITE1_READ_TIME=30)
add_definitions(-DONEWIRE__BIT_FORM_TIMER__WRITE0_DRIVE_HIGH_TIME=120)
add_definitions(-DONEWIRE__BIT_FORM_TIMER__WRITE0_READ_TIME=138)
add_definitions(-DONEWIRE__BIT_FORM_TIMER__RESET_DRIVE_HIGH_TIME=120)
add_definitions(-DONEWIRE__BIT_FORM_TIMER__RESET_READ_TIME=138)
