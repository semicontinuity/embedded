cmake_minimum_required(VERSION 3.11)
project(test_pcint)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        ../../../../cpu/avr/pin_change_int0.c
        ../../../../cpu/avr/pin_change_int0.h
        ../../../../cpu/avr/pin_change_int1.c
        ../../../../cpu/avr/pin_change_int1.h
        ../../../../cpu/avr/pin_change_int2.c
        ../../../../cpu/avr/pin_change_int2.h
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
        ../../bsp/drivers/in/button16.h
        main.c
        __all__.c
        )

include_directories(. ../../bsp ../../../.. /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(test_pcint ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega328P__)
add_definitions(-DF_CPU=16000000UL)
add_definitions(-DINLINE=)

add_definitions(-DIN__BUTTON1__PORT=D)
add_definitions(-DIN__BUTTON1__PIN=4)
add_definitions(-DIN__BUTTON2__PORT=D)
add_definitions(-DIN__BUTTON2__PIN=5)
add_definitions(-DIN__BUTTON3__PORT=D)
add_definitions(-DIN__BUTTON3__PIN=6)
add_definitions(-DIN__BUTTON4__PORT=D)
add_definitions(-DIN__BUTTON4__PIN=7)
add_definitions(-DIN__BUTTON5__PORT=D)
add_definitions(-DIN__BUTTON5__PIN=3)
add_definitions(-DIN__BUTTON6__PORT=D)
add_definitions(-DIN__BUTTON6__PIN=2)
add_definitions(-DIN__BUTTON7__PORT=B)
add_definitions(-DIN__BUTTON7__PIN=3)
add_definitions(-DIN__BUTTON8__PORT=B)
add_definitions(-DIN__BUTTON8__PIN=0)
add_definitions(-DIN__BUTTON9__PORT=C)
add_definitions(-DIN__BUTTON9__PIN=3)
add_definitions(-DIN__BUTTON10__PORT=C)
add_definitions(-DIN__BUTTON10__PIN=1)
add_definitions(-DIN__BUTTON11__PORT=B)
add_definitions(-DIN__BUTTON11__PIN=5)
add_definitions(-DIN__BUTTON12__PORT=B)
add_definitions(-DIN__BUTTON12__PIN=1)
add_definitions(-DIN__BUTTON13__PORT=C)
add_definitions(-DIN__BUTTON13__PIN=2)
add_definitions(-DIN__BUTTON14__PORT=C)
add_definitions(-DIN__BUTTON14__PIN=0)
add_definitions(-DIN__BUTTON15__PORT=B)
add_definitions(-DIN__BUTTON15__PIN=4)
add_definitions(-DIN__BUTTON16__PORT=B)
add_definitions(-DIN__BUTTON16__PIN=2)

add_definitions(-DOUT__LED1__PORT=C)
add_definitions(-DOUT__LED1__PIN=4)
add_definitions(-DOUT__LED2__PORT=C)
add_definitions(-DOUT__LED2__PIN=5)
add_definitions(-DOUT__LED3__PORT=D)
add_definitions(-DOUT__LED3__PIN=0)
