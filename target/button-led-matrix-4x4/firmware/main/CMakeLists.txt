cmake_minimum_required(VERSION 3.11)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        ../../../../cpu/avr/timer0.c
        ../../../../cpu/avr/timer0.h
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
        ../../bsp/drivers/keyboard__pins.h
        keyboard.c
        keyboard.h
        I2CSlave.c
        I2CSlave.h
        comm__switch.c
        comm.h
        main.c
        __all__.c
        )

include_directories(. ../../bsp ../../../.. /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(main ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega48__)
add_definitions(-DF_CPU=8000000UL)
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

add_definitions(-Dtimer0__overflow__run=keyboard__debounce_timer__expired)
add_definitions(-DKEYBOARD__PORT_B__PREVIOUS_STATE__REG=11)
add_definitions(-DKEYBOARD__PORT_C__PREVIOUS_STATE__REG=12)
add_definitions(-DKEYBOARD__PORT_D__PREVIOUS_STATE__REG=13)
add_definitions(-DKEYBOARD__PORT_B__MASK__REG=16)
add_definitions(-DKEYBOARD__PORT_C__MASK__REG=17)
add_definitions(-DKEYBOARD__PORT_D__MASK__REG=18)

add_definitions(-DTX_RING_BUFFER__ALIGNED=1)
add_definitions(-DTX_RING_BUFFER__SIZE=128)
add_definitions(-DTX_RING_BUFFER__HEAD__REG=26)
add_definitions(-DTX_RING_BUFFER__TAIL__REG=28)
add_definitions(-DTX_RING_BUFFER__NOT_EMPTY__HOST=GPIOR0)
add_definitions(-DTX_RING_BUFFER__NOT_EMPTY__BIT=1)
add_definitions(-DTX_RING_BUFFER__NOT_EMPTY__IN_BIT_IO_MEM=1)
add_definitions(-DTX_RING_BUFFER__NOT_FULL__HOST=GPIOR0)
add_definitions(-DTX_RING_BUFFER__NOT_FULL__BIT=0)
add_definitions(-DTX_RING_BUFFER__NOT_FULL__IN_BIT_IO_MEM=1)

add_definitions(-DTWI__SLAVE__ADDRESS=0x10)

add_definitions(-DREFRESH__HOST=GPIOR0)
add_definitions(-DREFRESH__BIT=2)
