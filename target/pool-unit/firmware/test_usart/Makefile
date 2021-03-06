BIN=test_usart

# Headers that don't have c-files with same name
#  but project depends on them
#INDEPENDENT_HEADERS=includes.h

# Here are STDPeriphLib objects used in project
SPL=
SPL+=misc
SPL+=stm32f10x_adc
SPL+=stm32f10x_bkp
SPL+=stm32f10x_can
SPL+=stm32f10x_cec
SPL+=stm32f10x_crc
SPL+=stm32f10x_dac
SPL+=stm32f10x_dbgmcu
SPL+=stm32f10x_dma
SPL+=stm32f10x_exti
SPL+=stm32f10x_flash
SPL+=stm32f10x_fsmc
SPL+=stm32f10x_gpio
SPL+=stm32f10x_i2c
SPL+=stm32f10x_iwdg
SPL+=stm32f10x_pwr
SPL+=stm32f10x_rcc
SPL+=stm32f10x_rtc
SPL+=stm32f10x_sdio
SPL+=stm32f10x_spi
SPL+=stm32f10x_tim
SPL+=stm32f10x_usart
SPL+=stm32f10x_wwdg

HAL=
HAL+=stm32f1xx_hal
HAL+=stm32f1xx_hal_cortex
HAL+=stm32f1xx_hal_dma
HAL+=stm32f1xx_hal_flash
HAL+=stm32f1xx_hal_gpio
HAL+=stm32f1xx_hal_gpio_ex
HAL+=stm32f1xx_hal_rcc
HAL+=stm32f1xx_hal_uart

STM32_STD_PERIPH_LIB?=./STM32F10x_StdPeriph_Lib_V3.5.0
STM32_STD_PERIPH_LIB__SRC?=$(STM32_STD_PERIPH_LIB)/Libraries/STM32F10x_StdPeriph_Driver/src
STM32_STD_PERIPH_LIB__INC?=$(STM32_STD_PERIPH_LIB)/Libraries/STM32F10x_StdPeriph_Driver/inc

CMSIS__PATH?=cmsis-
CMSIS__SRC?=$(CMSIS__PATH)
CMSIS__INC?=$(CMSIS__PATH)

HAL__SRC?=$(HAL__PATH)/Src
HAL__INC?=$(HAL__PATH)/Inc

OBJDIR=mk

#INDEPENDENT_HEADERS+=$(STM32_STD_PERIPH_LIB__INC)/stm32f10x_conf.h

TOOLS_PREFIX=arm-none-eabi-

CPFLAGS=-Obinary
ODFLAGS=-S

CFLAGS=-c -std=c99 -mcpu=cortex-m3 -mthumb -Wall -Werror -mapcs-frame -Os
#CFLAGS=-c -mcpu=cortex-m3 -mthumb -Wall -Werror -mapcs-frame -D__thumb2__=1 -Os
CFLAGS+=-msoft-float -gdwarf-2 -mno-sched-prolog -fno-hosted -mtune=cortex-m3
CFLAGS+=-march=armv7-m -mfix-cortex-m3-ldrd -ffunction-sections -fdata-sections
CFLAGS+=-I$(CMSIS__INC) -I$(CMSIS_NEW__PATH)/Device/ST/STM32F1xx/Include -I$(CMSIS_NEW__PATH)/Include -I$(STM32_STD_PERIPH_LIB__INC) -I$(HAL__INC) -I.
#CFLAGS+=-DSTM32F10X_MD
CFLAGS+=-DSTM32F103x6

LDFLAGS=-static -mcpu=cortex-m3 -mthumb -mthumb-interwork -Wl,--start-group
LDFLAGS+=-L$(TOOLS_PATH)/lib/thumb -lc -lg -lstdc++ -lsupc++ -lgcc -lm
#LDFLAGS+=-L$(TOOLS_PATH)/lib/thumb2 -lc -lg -lstdc++ -lsupc++ -lgcc -lm
LDFLAGS+=-Wl,--end-group -Xlinker -Map -Xlinker $(BIN).map -Xlinker
LDFLAGS+=-T $(CMSIS__SRC)/stm32f100rb_flash.ld -o $(BIN)
LDFLAGS+=-Wl,--gc-sections -Wl,-s

ASFLAGS=-mcpu=cortex-m3 -I -I$(STM32_STD_PERIPH_LIB__INC) -gdwarf-2 -gdwarf-2

CC=$(TOOLS_PREFIX)gcc
AS=$(TOOLS_PREFIX)as
SIZE=$(TOOLS_PREFIX)size
CP=$(TOOLS_PREFIX)objcopy
OD=$(TOOLS_PREFIX)objdump

# These are main project sources
SRC=$(wildcard *.c)
MAIN_OBJ=$(addprefix $(OBJDIR)/, $(SRC:%.c=%.o))

STM32_LIBSRC+=$(addprefix $(HAL__SRC)/, $(addsuffix .c, $(HAL)))
OBJ+=$(addprefix $(OBJDIR)/, $(addsuffix .o, $(HAL)))

OBJ+=$(OBJDIR)/startup.o
OBJ+=$(OBJDIR)/system_stm32f1xx.o
STM32_LIBSRC+=$(CMSIS_NEW__PATH)/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c


ALL_OBJ=$(OBJ) $(MAIN_OBJ)
ALL_SRC=$(SRC) $(STM32_LIBSRC)

all: $(BIN)

$(OBJDIR):
	mkdir $(OBJDIR)

#$(error $(STM32_STD_PERIPH_LIB__SRC)/%.c)
$(OBJDIR)/%.o: $(STM32_STD_PERIPH_LIB__SRC)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: $(HAL__SRC)/%.c
	$(CC) $(CFLAGS) $< -o $@

#$(OBJDIR)/system_stm32f10x.o: $(CMSIS__SRC)/system_stm32f10x.c
$(OBJDIR)/system_stm32f1xx.o: $(CMSIS_NEW__PATH)/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR)/startup.o: $(CMSIS__SRC)/startup_stm32f10x_md.s
	$(AS) $(ASFLAGS) $(CMSIS__SRC)/startup_stm32f10x_md.s -o $(OBJDIR)/startup.o

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(SRC) : %.c : %.h $(INDEPENDENT_HEADERS)
	@touch $@

%.h: ;

$(BIN): $(OBJDIR) $(ALL_OBJ)
	$(CC) $(ALL_OBJ) $(LDFLAGS)
	$(CP) $(CPFLAGS) $(BIN) $(BIN).bin
	$(OD) $(ODFLAGS) $(BIN) > $(BIN).list
	$(SIZE) -B $(BIN)

clean:
	rm -f $(ALL_OBJ) $(BIN).map $(BIN) $(BIN).list
	rmdir $(OBJDIR)

load: $(BIN)
	st-flash write $(BIN).bin 0x08000000


.PHONY: clean load
