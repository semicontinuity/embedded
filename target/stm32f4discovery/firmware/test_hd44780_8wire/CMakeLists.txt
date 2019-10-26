cmake_minimum_required(VERSION 3.11)
project(test_hd44780_8wire)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        app_lcd.h
        app_lcd.c
        defines.h
        main.c
        stm32fxxx_it.h
        stm32fxxx_it.c
        syscalls.c
        system_stm32f4xx.c

        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/stm32fxxx_hal.h
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-HAL_DRIVERS/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-HAL_DRIVERS/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h
        )

include_directories(
        .
        /opt/gcc-arm-none-eabi-8-2019-q3-update/arm-none-eabi/include
        /opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES
        /opt/stm32fxxx_hal_libraries/00-HAL_DRIVERS/CMSIS/Device/ST/STM32F4xx/Include
        /opt/stm32fxxx_hal_libraries/00-HAL_DRIVERS/STM32F4xx_HAL_Driver/Inc
        /opt/stm32fxxx_hal_libraries/00-HAL_DRIVERS/CMSIS/Include
)

add_executable( ${SOURCE_FILES})

add_definitions(-DSTM32F407xx)
add_definitions(-DSTM32F4xx)
add_definitions(-DSTM32F4_DISCOVERY)
add_definitions(-DHD44780_LCD__DONT_USE_BUSY_FLAG)
