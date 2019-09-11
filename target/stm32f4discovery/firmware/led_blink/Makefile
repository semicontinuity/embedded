################################################################################
# This Makefile uses build scrips from MIOS32 project
################################################################################

################################################################################
# following setup taken from environment variables
################################################################################

MIOS32_BOARD=MBHP_CORE_STM32F4
MIOS32_FAMILY=STM32F4xx
MIOS32_LCD=universal
MIOS32_PROCESSOR=STM32F407VG

PROCESSOR =	$(MIOS32_PROCESSOR)
FAMILY    = 	$(MIOS32_FAMILY)
BOARD	  = 	$(MIOS32_BOARD)
LCD       =     $(MIOS32_LCD)


################################################################################
# Source Files, include paths and libraries
################################################################################

THUMB_SOURCE    = main.c

# (following source stubs not relevant for Cortex M3 derivatives)
THUMB_AS_SOURCE =
ARM_SOURCE      =
ARM_AS_SOURCE   =

C_INCLUDE = 	-I .
A_INCLUDE = 	-I .

LIBS = 		


################################################################################
# Remaining variables
################################################################################

LD_FILE   = 	$(MIOS32_PATH)/etc/ld/$(FAMILY)/$(PROCESSOR).ld
PROJECT   = 	project

DEBUG     =	-g
OPTIMIZE  =	-Os

CFLAGS =	$(DEBUG) $(OPTIMIZE)


################################################################################
# Include source modules via additional makefiles
################################################################################

CMSIS_BOOT = cmsis_boot

# select driver library
DRIVER_LIB =	$(MIOS32_PATH)/drivers/$(FAMILY)/v1.1.0

# enhance include path
#C_INCLUDE +=	-I $(MIOS32_PATH)/mios32/$(FAMILY)
C_INCLUDE +=	-I $(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/inc -I $(DRIVER_LIB)/STM32_USB_Device_Library/Core/inc -I $(DRIVER_LIB)/STM32_USB_HOST_Library/Core/inc -I $(DRIVER_LIB)/STM32_USB_OTG_Driver/inc -I $(DRIVER_LIB)/CMSIS/Include -I $(DRIVER_LIB)/CMSIS/ST/STM32F4xx/Include -I $(DRIVER_LIB)/CMSIS/ST/STM32F4xx/Include
C_INCLUDE +=	-I $(CMSIS_BOOT)

CFLAGS += -DUSE_STDPERIPH_DRIVER -DUSB_SUPPORT_USER_STRING_DESC


# add modules to thumb sources
THUMB_SOURCE += \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/misc.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c \
	$(DRIVER_LIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c

# add modules to thumb sources
#THUMB_SOURCE += \
#	$(DRIVER_LIB)/STM32_USB_Device_Library/Core/src/usbd_core.c \
#	$(DRIVER_LIB)/STM32_USB_Device_Library/Core/src/usbd_ioreq.c \
#	$(DRIVER_LIB)/STM32_USB_Device_Library/Core/src/usbd_req.c \
#	$(DRIVER_LIB)/STM32_USB_HOST_Library/Core/src/usbh_core.c \
#	$(DRIVER_LIB)/STM32_USB_HOST_Library/Core/src/usbh_hcs.c \
#	$(DRIVER_LIB)/STM32_USB_HOST_Library/Core/src/usbh_ioreq.c \
#	$(DRIVER_LIB)/STM32_USB_HOST_Library/Core/src/usbh_stdreq.c \
#	$(DRIVER_LIB)/STM32_USB_OTG_Driver/src/usb_core.c \
#	$(DRIVER_LIB)/STM32_USB_OTG_Driver/src/usb_dcd.c \
#	$(DRIVER_LIB)/STM32_USB_OTG_Driver/src/usb_dcd_int.c \
#	$(DRIVER_LIB)/STM32_USB_OTG_Driver/src/usb_hcd.c \
#	$(DRIVER_LIB)/STM32_USB_OTG_Driver/src/usb_hcd_int.c \
#	$(DRIVER_LIB)/STM32_USB_OTG_Driver/src/usb_otg.c

THUMB_SOURCE += \
	$(CMSIS_BOOT)/startup/startup_stm32f4xx.c \
	$(CMSIS_BOOT)/system_stm32f4xx.c


THUMB_AS_SOURCE += 

# common make rules
# Please keep this include statement at the end of this Makefile. Add new modules above.
include $(MIOS32_PATH)/include/makefile/common.mk
