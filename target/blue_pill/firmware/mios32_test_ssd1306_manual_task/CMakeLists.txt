cmake_minimum_required(VERSION 3.11)
project(mios32_test_ssd1306_manual_task)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        app.c
        app.h
        mios32_config.h

        ../../../../../../../github.com/semicontinuity/mios32/include/mios32/mios32_din.h
        ../../../../../../../github.com/semicontinuity/mios32/include/mios32/mios32_enc.h
        ../../../../../../../github.com/semicontinuity/mios32/include/mios32/mios32_lcd.h

        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_com.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_din.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_dout.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_enc.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_enc28j60.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_iic_bs.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_iic_midi.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_lcd.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_mf.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_midi.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_osc.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_sdcard.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_spi_midi.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_srio.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_timestamp.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/mios32_uart_midi.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/common/printf-stdarg.c

        ../../../../../../../github.com/semicontinuity/mios32/modules/app_lcd/universal/app_lcd.h
        ../../../../../../../github.com/semicontinuity/mios32/modules/app_lcd/universal/app_lcd.c
        ../../../../../../../github.com/semicontinuity/mios32/modules/glcd_font/glcd_font.h


        ../../../../../../../github.com/semicontinuity/mios32/programming_models/traditional/startup_stm32f10x_md.c

        ../../../../../../../github.com/semicontinuity/mios32/programming_models/traditional/main.c
        ../../../../../../../github.com/semicontinuity/mios32/programming_models/traditional/strtol.c
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/tasks.c
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/list.c
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/queue.c
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/timers.c
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/portable/MemMang/heap_4.c

        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_ain.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_board.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_bsl.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_delay.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_i2s.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_iic.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_irq.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_spi.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_stopwatch.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_sys.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_timer.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_uart.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_usb.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_usb_com.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/mios32_usb_midi.c
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/usb_conf.h
        ../../../../../../../github.com/semicontinuity/mios32/mios32/STM32F10x/usb_istr.h

        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/CMSIS/CM3/CoreSupport/core_cm3.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/CMSIS/CM3/CoreSupport/core_cm3.h

        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h

        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/misc.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_adc.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_can.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_crc.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_dbgmcu.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_dma.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_exti.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_flash.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_fsmc.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_gpio.h

        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_i2c.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_iwdg.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_pwr.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_rcc.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_rtc.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_sdio.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_spi.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_tim.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_usart.h
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc/stm32f10x_wwdg.h

        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/misc.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c
        )
#        ../../../../../../../github.com/semicontinuity/mios32/programming_models/traditional/mini_cpp.cpp
#../../../../../../../github.com/semicontinuity/mios32/programming_models/traditional/freertos_heap.cpp


include_directories(
        .
        /opt/gcc-arm-none-eabi-8-2018-q4-major/arm-none-eabi/include
        ../../../../../../../github.com/semicontinuity/mios32/include/mios32
        ../../../../../../../github.com/semicontinuity/mios32/programming_models/traditional
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/include
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/portable/GCC/ARM_CM3
        ../../../../../../../github.com/semicontinuity/mios32/FreeRTOS/Source/portable/MemMang
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/STM32F10x_StdPeriph_Driver/inc
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/CMSIS/CM3/CoreSupport
        ../../../../../../../github.com/semicontinuity/mios32/drivers/STM32F10x/v3.3.0/CMSIS/CM3/DeviceSupport/ST/STM32F10x


        ../../../../../../../github.com/semicontinuity/mios32/modules/glcd_font
)

add_executable(mios32_test_ssd1306_manual_task ${SOURCE_FILES})

add_definitions(-DMIOS32_BOARD=BLUE_PILL)
add_definitions(-DMIOS32_FAMILY=STM32F10x)
add_definitions(-DMIOS32_LCD=clcd_parallel)
add_definitions(-DMIOS32_PROCESSOR=STM32F103CB)

add_definitions(-DMIOS32_BOARD_BLUE_PILL)
add_definitions(-DMIOS32_BOARD_STR=\"BLUE_PILL\")
add_definitions(-DMIOS32_LCD_cldc_parallel)
add_definitions(-DMIOS32_LCD_STR=\"clcd_parallel\")
add_definitions(-DMIOS32_FAMILY_STM32F10x)
add_definitions(-DMIOS32_FAMILY_STR=\"STM32F10x\")
add_definitions(-DMIOS32_PROCESSOR_STM32F103CB)

add_definitions(-DUSE_STDPERIPH_DRIVER)
add_definitions(-DUSB_SUPPORT_USER_STRING_DESC)
