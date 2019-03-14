cmake_minimum_required(VERSION 3.11)
project(console_i2c_slave)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        comm__switch.c
        comm.h
        I2CSlave.c
        I2CSlave.h
        services/console_i2c_slave.c
        services/console_i2c_slave.h
        services/console.h
        services/console.c
        services/console__in.h
        services/console__in__polled.c
        services/console__out.h
        services/console__out__buffered.c
        util/formatter.h
        util/formatter.c
        util/parser.h
        util/parser.c
        main.c
        __all__.c
        )

include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(console_i2c_slave ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega48__)
add_definitions(-DF_CPU=8000000UL)

add_definitions(-DUSART0__BAUD_RATE=38400UL)
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

add_definitions(-DTWI__SLAVE__ADDRESS=0x10)
