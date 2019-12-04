cmake_minimum_required(VERSION 3.11)
project(test_hd44780_8wire_sdcard_tm)

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

        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/tm_stm32_delay.h
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/tm_stm32_delay.c
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/tm_stm32_disco.h
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/tm_stm32_disco.c
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/tm_stm32_gpio.h
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/tm_stm32_gpio.c
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/tm_stm32_rcc.h
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/tm_stm32_rcc.c
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/tm_stm32_fatfs.h
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/tm_stm32_fatfs.c

        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/fatfs/ff.h
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/fatfs/ff.c
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/fatfs/diskio.h
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/fatfs/diskio.c
#        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/fatfs/drivers/fatfs_sd_sdio.h
#        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/fatfs/drivers/fatfs_sd_sdio.c
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/fatfs/drivers/fatfs_sd.h
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/fatfs/drivers/fatfs_sd.c
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/fatfs/option/ccsbcs.c
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/fatfs/option/syscall.c
        )

include_directories(
        .
        ../../../../../../../../../../opt/gcc-arm-none-eabi-8-2019-q3-update/arm-none-eabi/include
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-HAL_DRIVERS/CMSIS/Device/ST/STM32F4xx/Include
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-HAL_DRIVERS/STM32F4xx_HAL_Driver/Inc
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-HAL_DRIVERS/CMSIS/Include
        ../../../../../../../../../../opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/fatfs/
)

add_executable( ${SOURCE_FILES})

add_definitions(-DSTM32F407xx)
add_definitions(-DSTM32F4xx)
add_definitions(-DSTM32F4_DISCOVERY)
add_definitions(-DHD44780_LCD__DONT_USE_BUSY_FLAG)
