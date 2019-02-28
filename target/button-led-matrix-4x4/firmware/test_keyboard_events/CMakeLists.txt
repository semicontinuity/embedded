cmake_minimum_required(VERSION 3.11)
project(test_keyboard_events)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        ../../../../cpu/avr/timer0.c
        ../../../../cpu/avr/timer0.h
        ../../../../cpu/avr/pin_change_int0.c
        ../../../../cpu/avr/pin_change_int0.h
        ../../../../cpu/avr/pin_change_int1.c
        ../../../../cpu/avr/pin_change_int1.h
        ../../../../cpu/avr/pin_change_int2.c
        ../../../../cpu/avr/pin_change_int2.h
        ../../../../services/tx_ring_buffer.h
        ../../../../services/tx_ring_buffer.c
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
        ../../bsp/drivers/keyboard__debounce_timer.c
        ../../bsp/drivers/keyboard__debounce_timer.h
        main.c
        keyboard__interrupts.c
        keyboard__interrupts.h
        keyboard__pins.h
        __all__.c
        )

include_directories(. ../../bsp ../../../.. /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(test_keyboard_events ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega328P__)
add_definitions(-DF_CPU=16000000UL)
add_definitions(-DINLINE=)

add_definitions(-DIN__BUTTON0__PORT=D)
add_definitions(-DIN__BUTTON0__PIN=4)
add_definitions(-DIN__BUTTON1__PORT=D)
add_definitions(-DIN__BUTTON1__PIN=5)
add_definitions(-DIN__BUTTON2__PORT=D)
add_definitions(-DIN__BUTTON2__PIN=6)
add_definitions(-DIN__BUTTON3__PORT=D)
add_definitions(-DIN__BUTTON3__PIN=7)
add_definitions(-DIN__BUTTON4__PORT=D)
add_definitions(-DIN__BUTTON4__PIN=3)
add_definitions(-DIN__BUTTON5__PORT=D)
add_definitions(-DIN__BUTTON5__PIN=2)
add_definitions(-DIN__BUTTON6__PORT=B)
add_definitions(-DIN__BUTTON6__PIN=3)
add_definitions(-DIN__BUTTON7__PORT=B)
add_definitions(-DIN__BUTTON7__PIN=0)
add_definitions(-DIN__BUTTON8__PORT=C)
add_definitions(-DIN__BUTTON8__PIN=3)
add_definitions(-DIN__BUTTON9__PORT=C)
add_definitions(-DIN__BUTTON9__PIN=1)
add_definitions(-DIN__BUTTON10__PORT=B)
add_definitions(-DIN__BUTTON10__PIN=5)
add_definitions(-DIN__BUTTON11__PORT=B)
add_definitions(-DIN__BUTTON11__PIN=1)
add_definitions(-DIN__BUTTON12__PORT=C)
add_definitions(-DIN__BUTTON12__PIN=2)
add_definitions(-DIN__BUTTON13__PORT=C)
add_definitions(-DIN__BUTTON13__PIN=0)
add_definitions(-DIN__BUTTON14__PORT=B)
add_definitions(-DIN__BUTTON14__PIN=4)
add_definitions(-DIN__BUTTON15__PORT=B)
add_definitions(-DIN__BUTTON15__PIN=2)

add_definitions(-DOUT__LED1__PORT=C)
add_definitions(-DOUT__LED1__PIN=4)
add_definitions(-DOUT__LED2__PORT=C)
add_definitions(-DOUT__LED2__PIN=5)
add_definitions(-DOUT__LED3__PORT=D)
add_definitions(-DOUT__LED3__PIN=0)

add_definitions(-Dpin_change_int0__run=keyboard__port_b__on_change)
add_definitions(-Dpin_change_int1__run=keyboard__port_c__on_change)
add_definitions(-Dpin_change_int2__run=keyboard__port_d__on_change)
add_definitions(-Dtimer0__overflow__run=keyboard__debounce_timer__expired)

add_definitions(-DUSART0__BAUD_RATE=9600UL)
add_definitions(-Dusart0__tx__has_next=comm__tx__has_next)
add_definitions(-Dusart0__tx__next=comm__tx__next)
add_definitions(-Dusart0__tx__on_done=comm__tx__on_done)
add_definitions(-Dusart0__tx__data_register_empty__interrupt__ATTRS=)
add_definitions(-DTX_RING_BUFFER__ALIGNED=1)
add_definitions(-DTX_RING_BUFFER__SIZE=128)
add_definitions(-DTX_RING_BUFFER__HEAD__REG=26)
add_definitions(-DTX_RING_BUFFER__TAIL__REG=28)
add_definitions(-DTX_RING_BUFFER__NOT_EMPTY__HOST=usart0__tx__data_register_empty__interrupt__enabled__HOST)
add_definitions(-DTX_RING_BUFFER__NOT_EMPTY__BIT=usart0__tx__data_register_empty__interrupt__enabled__BIT)
add_definitions(-DTX_RING_BUFFER__NOT_FULL__HOST=GPIOR0)
add_definitions(-DTX_RING_BUFFER__NOT_FULL__BIT=0)
add_definitions(-DTX_RING_BUFFER__NOT_FULL__IN_BIT_IO_MEM=1)
