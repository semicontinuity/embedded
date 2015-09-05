cmake_minimum_required(VERSION 2.8.4)
project(test_soft_usart)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c
    soft_usart.c
    soft_usart__timer.h
    ../../../../cpu/avr/int0.c
    ../../../../ ../../../../../../avrgcc/avr/include/avr/iom168.h
)


include_directories(. ../../bsp ../../../../ ../../../../../../avrgcc/avr/include ../../../../../../avrgcc/lib/gcc/avr/4.8.1/include)
add_executable(test_soft_usart ${SOURCE_FILES})


add_definitions(-D__AVR_ATmega168__)
add_definitions(-DINLINE=)
add_definitions(-DMCU=atmega168)
add_definitions(-DOPT="2 -Wa,-a,-ad")


# System
# ==============================================================================
add_definitions(-DF_CPU=12000000UL)

# Global
# ==============================================================================
add_definitions(-DTEMP_REG=2)

# Soft USART
# ==============================================================================
add_definitions(-DINT0__PULLUP=1)
add_definitions(-Dint0__run=soft_usart__on_start_bit_detected)
add_definitions(-DTIMER0_COMPA_vect_naked=1)
add_definitions(-Dtimer0__comp_a__run=soft_usart__rx__thread__run)

add_definitions(-DSOFT_USART__RX__DATA__REG=15)
add_definitions(-DSOFT_USART__RX__PORT=B)
add_definitions(-DSOFT_USART__RX__PIN=2)

