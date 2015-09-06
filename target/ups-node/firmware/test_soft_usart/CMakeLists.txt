cmake_minimum_required(VERSION 2.8.4)
project(test_soft_usart)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c
    soft_usart__timer.h
    soft_usart__rx.c
    soft_usart__rx.h
    soft_usart__tx.c
    soft_usart__tx.h
    ../../../../cpu/avr/int0.c
    ../../../../ ../../../../../../avrgcc/avr/include/avr/iom168.h
)


include_directories(. ../../bsp ../../../../ ../../../../../../avrgcc/avr/include ../../../../../../avrgcc/lib/gcc/avr/4.8.1/include)
add_executable(test_soft_usart ${SOURCE_FILES})


add_definitions(-D__AVR_ATmega168__)
add_definitions(-DINLINE=)
add_definitions(-DMCU=atmega168)
add_definitions(-DOPT="2 -Wa,-a,-ad -finline-functions -fpredictive-commoning -fgcse-after-reload -fvect-cost-model  -fipa-cp-clone -ftree-loop-distribute-patterns -ftree-slp-vectorize")


# System
# ==============================================================================
add_definitions(-DF_CPU=20000000UL)

# Global
# ==============================================================================
add_definitions(-DTEMP_REG=2)

# Soft USART
# ==============================================================================
add_definitions(-DINT0__PULLUP=1)
add_definitions(-Dint0__run=soft_usart__rx__thread__start)
#add_definitions(-DTIMER0_COMPA_vect_naked=1)
add_definitions(-Dtimer0__comp_a__run=soft_usart__rx__thread__run)
add_definitions(-Dsoft_usart__rx__detector__start=int0__start)
add_definitions(-Dsoft_usart__rx__detector__stop=int0__stop)
add_definitions(-DSOFT_USART__RX__THREAD__IP__REG=16)
add_definitions(-DSOFT_USART__RX__DATA__REG=15)
add_definitions(-DSOFT_USART__RX__PORT=B)
add_definitions(-DSOFT_USART__RX__PIN=2)

#add_definitions(-DTIMER0_COMPB_vect_naked=1)
add_definitions(-Dtimer0__comp_b__run=soft_usart__tx__thread__run)
add_definitions(-DSOFT_USART__TX__THREAD__IP__REG=18)
add_definitions(-DSOFT_USART__TX__DATA__REG=14)
add_definitions(-DSOFT_USART__TX__PORT=B)
add_definitions(-DSOFT_USART__TX__PIN=3)

