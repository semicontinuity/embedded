cmake_minimum_required(VERSION 2.8.4)
project(test_soft_spi)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c
)


include_directories(. ../../bsp ../../../../ ../../../../../../avrgcc/avr/include ../../../../../../avrgcc/lib/gcc/avr/4.8.1/include)
add_executable(test_soft_spi ${SOURCE_FILES})


add_definitions(-D__AVR_ATmega48__)
add_definitions(-DMCU=atmega48)

# System
# ==============================================================================
add_definitions(-DF_CPU=1000000UL)


# Soft SPI
# ==============================================================================
add_definitions(-DMOSI__PORT=C)
add_definitions(-DMOSI__PIN=5)
add_definitions(-DSCK__PORT=C)
add_definitions(-DSCK__PIN=4)
