cmake_minimum_required(VERSION 3.11)
project(test_i2c_slave_led_int2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        ../../../../cpu/avr/twi.h
        ../../bsp/drivers/twi_slave.c
        ../../bsp/drivers/twi_slave.h
        ../../bsp/drivers/out/led1.h
        main.c
        __all__.c
        )

include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(test_i2c_slave_led2_int2 ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega328P__)
add_definitions(-DF_CPU=16000000UL)
#add_definitions(-DTWI__SLAVE__THREAD__IP__REG=30)

add_definitions(-DOUT__LED1__PORT=B)
add_definitions(-DOUT__LED1__PIN=5)

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
