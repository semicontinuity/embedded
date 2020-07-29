cmake_minimum_required(VERSION 3.11)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        ../../../../cpu/avr/timer0.c
        ../../../../cpu/avr/timer0.h
        main.c
        soft_usart__timer.h
        soft_usart__tx.h
        soft_usart__tx__pin.h
        soft_usart__tx__pin.h
        soft_usart__tx__thread.h
        __all__.c
        )

include_directories(. ../../bsp ../../../.. /usr/lib/gcc/avr/5.4.0/include /usr/lib/avr/include)
add_executable(main ${SOURCE_FILES})

add_definitions(-D__AVR_ATtiny85__)
add_definitions(-DF_CPU=1000000UL)
add_definitions(-DINLINE=)

#add_definitions(-DTIMER0_COMPA_vect_naked=1)
add_definitions(-Dtimer0__comp_a__run=soft_usart__tx__thread__run)
add_definitions(-Dsoft_usart__tx__thread__is_runnable=timer0__compare_a__interrupt__is_enabled)
add_definitions(-Dsoft_usart__tx__thread__on_finish=soft_usart__timer__stop)

add_definitions(-DSOFT_USART__TX__PORT=B)
add_definitions(-DSOFT_USART__TX__PIN=4)
add_definitions(-DSOFT_USART__BAUD_RATE=2400UL)
