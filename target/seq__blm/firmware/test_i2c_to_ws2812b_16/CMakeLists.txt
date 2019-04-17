cmake_minimum_required(VERSION 3.11)
project(test_i2c_to_ws2812b_16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        ../../../../cpu/avr/twi.h
        ../../bsp/drivers/comm/twi_slave.c
        ../../bsp/drivers/comm/twi_slave.h
        ../../bsp/drivers/comm/ws2812b.c
        ../../bsp/drivers/comm/ws2812b.h
        ../../bsp/drivers/out/alarm.h
        comm.c
        main.c
        __all__.c
        )

include_directories(. ../../bsp ../../../../ /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(test_i2c_to_ws2812b_16 ${SOURCE_FILES})

add_definitions(-D__AVR_ATmega48__)
add_definitions(-DF_CPU=8000000UL)

#add_definitions(-DTWI__SLAVE__THREAD__IP__REG=30)
add_definitions(-DTWI__SLAVE__ADDRESS=0x50)
#add_definitions(-DFIXED_REGISTERS=-ffixed-r30 -ffixed-r31)

add_definitions(-DOUT__LED1__PORT=D)
add_definitions(-DOUT__LED1__PIN=0)
