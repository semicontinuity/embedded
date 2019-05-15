cmake_minimum_required(VERSION 3.11)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        ../../../../cpu/avr/timer0.c
        ../../../../cpu/avr/timer0.h
        ../../bsp/drivers/in/button0.h
        ../../bsp/drivers/in/button1.h
        ../../bsp/drivers/in/button2.h
        ../../bsp/drivers/in/button3.h
        ../../bsp/drivers/in/button4.h
        ../../bsp/drivers/in/button5.h
        ../../bsp/drivers/in/button6.h
        ../../bsp/drivers/in/button7.h
        ../../bsp/drivers/in/button8.h
        ../../bsp/drivers/in/button9.h
        ../../bsp/drivers/in/button10.h
        ../../bsp/drivers/in/button11.h
        ../../bsp/drivers/in/button12.h
        ../../bsp/drivers/in/button13.h
        ../../bsp/drivers/in/button14.h
        ../../bsp/drivers/in/button15.h
        ../../bsp/drivers/keyboard__pins__physical.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__debounce_timer__timer0.c
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping.h
        ../../../../cpu/avr/drivers/keyboard/keyboard__pins__mapping.c
        ../../../../cpu/avr/services/keyboard/keyboard.c
        ../../../../cpu/avr/services/keyboard/keyboard.h

        ../../../../services/tx_ring_buffer.h
        ../../../../services/tx_ring_buffer.c

        I2CSlave.c
        I2CSlave.h
        comm__switch.c
        comm.h

        comm_keyboard.h
        comm_keyboard.c

        leds.c
        main.c
        __all__.c
        )

include_directories(. ../../bsp ../../../.. /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(main ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega48__)
add_definitions(-DF_CPU=8000000UL)
add_definitions(-DINLINE=)

add_definitions(-DREFRESH__HOST=GPIOR0)
add_definitions(-DREFRESH__BIT=2)

include(CMakeLists.io.txt)
include(CMakeLists.keyboard.txt)
include(CMakeLists.comm_keyboard_simple.txt)
include(CMakeLists.twi.txt)