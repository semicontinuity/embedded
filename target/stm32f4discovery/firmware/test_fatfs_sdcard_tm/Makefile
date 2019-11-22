BIN=test_fatfs_sdcard_tm

# Headers that don't have c-files with same name
#  but project depends on them
INDEPENDENT_HEADERS=defines.h


FF=
FF+=diskio
FF+=ff

FF_DRV=
FF_DRV+=fatfs_sd_sdio

FF_OPT=
FF_OPT+=ccsbcs
FF_OPT+=syscall

FF_DIR?=/projects/stm32fxxx_hal_libraries/00-STM32_LIBRARIES/fatfs
FF_SRC?=$(FF_DIR)
FF_INC?=$(FF_DIR)
FF_LIBOBJ=$(addprefix $(OBJDIR)/, $(addsuffix .o, $(FF)))
FF_OPTOBJ=$(addprefix $(OBJDIR)/, $(addsuffix .o, $(FF_OPT)))
FF_DRVOBJ=$(addprefix $(OBJDIR)/, $(addsuffix .o, $(FF_DRV)))


TM=
TM+=tm_stm32_delay
TM+=tm_stm32_disco
TM+=tm_stm32_gpio
TM+=tm_stm32_rcc
TM+=tm_stm32_fatfs

TM_DIR?=/projects/stm32fxxx_hal_libraries/00-STM32_LIBRARIES
TM_SRC?=$(TM_DIR)
TM_INC?=$(TM_DIR)
#TM_LIBSRC=$(addprefix $(TM_SRC)/, $(addsuffix .c, $(TM)))
TM_LIBOBJ=$(addprefix $(OBJDIR)/, $(addsuffix .o, $(TM)))


HAL=
HAL+=stm32f4xx_hal
HAL+=stm32f4xx_hal_cortex
HAL+=stm32f4xx_hal_dma
HAL+=stm32f4xx_hal_gpio
HAL+=stm32f4xx_hal_sd
HAL+=stm32f4xx_hal_rcc
HAL+=stm32f4xx_ll_sdmmc

HAL_DIR?=/projects/stm32fxxx_hal_libraries/00-HAL_DRIVERS/STM32F4xx_HAL_Driver
HAL_SRC?=$(HAL_DIR)/Src
HAL_INC?=$(HAL_DIR)/Inc
#HAL_SRC_FILES=$(wildcard $(HAL_SRC)/*.c)
#HAL_OBJ=$(addprefix $(OBJDIR)/, $(HAL_SRC_FILES:$(HAL_SRC)/%.c=%.o))
HAL_LIBSRC=$(addprefix $(HAL_SRC)/, $(addsuffix .c, $(HAL)))
HAL_LIBOBJ=$(addprefix $(OBJDIR)/, $(addsuffix .o, $(HAL)))


CMSIS?=/projects/stm32fxxx_hal_libraries/00-HAL_DRIVERS/CMSIS
CMSIS__SRC?=$(CMSIS)/Device/ST/STM32F4xx/Source
CMSIS__INC?=$(CMSIS)/Device/ST/STM32F4xx/Include


OBJDIR=mk


TOOLS_PREFIX=arm-none-eabi-

CPFLAGS=-Obinary
ODFLAGS=-S

# works (but FPU not enabled)
CFLAGS += -mcpu=cortex-m4 -mlittle-endian -ffunction-sections -fdata-sections -fomit-frame-pointer
CFLAGS += -I.
CFLAGS += -I$(TM_INC)
CFLAGS += -I$(CMSIS__INC) -I$(CMSIS)/Include
CFLAGS += -I$(HAL_INC)
CFLAGS += -I$(FF_INC) -I$(FF_INC)/drivers


#CFLAGS=-c -mcpu=cortex-m3 -mthumb -Wall -Werror -mapcs-frame -D__thumb2__=1 -Os
#CFLAGS+=-msoft-float -gdwarf-2 -mno-sched-prolog -fno-hosted -mtune=cortex-m3
#CFLAGS+=-march=armv7-m -mfix-cortex-m3-ldrd -ffunction-sections -fdata-sections
#CFLAGS+=-I./cmsis -I$(STM32_STD_PERIPH_LIB__INC) -I$(STM32_USB_LIB__INC) -I.
CFLAGS+=-DSTM32F407xx -DSTM32F4xx -DSTM32F4_DISCOVERY

# default linker flags
LD_FILE=/projects/stm32fxxx_hal_libraries/01-STM32Fxxx_SW4STM32_CMSIS_Default_Project/LinkerScript.ld
LDFLAGS += -T $(LD_FILE) -mthumb -u _start -Xlinker -M -Xlinker -Map=$(BIN).map
#LDFLAGS += -nostartfiles
LDFLAGS += -Wl,--gc-section

#LDFLAGS += -lstdc++ 

# for https://launchpad.net/gcc-arm-embedded: enable newlib-nano for better performance
# not compatible with other toolchains (users have to switch to new version, or disable the line below)
#LDFLAGS += --specs=nano.specs


ASFLAGS=-mcpu=cortex-m4

CC=$(TOOLS_PREFIX)gcc
AS=$(TOOLS_PREFIX)as
SIZE=$(TOOLS_PREFIX)size
CP=$(TOOLS_PREFIX)objcopy
OD=$(TOOLS_PREFIX)objdump

# These are main project sources
SRC=$(wildcard *.c)
MAIN_OBJ=$(addprefix $(OBJDIR)/, $(SRC:%.c=%.o))

#STM32_LIBSRC=$(addprefix $(STM32_STD_PERIPH_LIB__SRC)/, $(addsuffix .c, $(SPL)))

OBJ=
#OBJ=$(addprefix $(OBJDIR)/, $(addsuffix .o, $(SPL)))

OBJ+=$(OBJDIR)/startup.o
#STM32_LIBSRC+=cmsis/system_stm32f10x.c

# USB library sources
#USB_SRC=$(wildcard $(STM32_USB_LIB__SRC)/*.c)
#USB_OBJ=$(addprefix $(OBJDIR)/, $(USB_SRC:$(STM32_USB_LIB__SRC)/%.c=%.o))

ALL_OBJ=$(OBJ) $(MAIN_OBJ) $(TM_LIBOBJ) $(HAL_LIBOBJ) $(FF_LIBOBJ) $(FF_OPTOBJ) $(FF_DRVOBJ)
#ALL_OBJ=$(ALL_OBJ) $(HAL_OBJ)

#ALL_SRC=$(SRC) $(STM32_LIBSRC) $(USB_SRC)
#ALL_SRC=$(SRC)

all: $(BIN)

$(OBJDIR):
	mkdir $(OBJDIR)

#$(OBJDIR)/%.o: $(HAK_SRC)/%.c
#	$(CC) $(CFLAGS) -c $< -o $@

#$(OBJDIR)/system_stm32f10x.o: ./cmsis/system_stm32f10x.c
#	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/startup.o: $(CMSIS__SRC)/Templates/gcc/startup_stm32f407xx.s
	$(AS) $(ASFLAGS) $(CMSIS__SRC)/Templates/gcc/startup_stm32f407xx.s -o $(OBJDIR)/startup.o

#$(OBJDIR)/startup.o: ./cmsis/startup_stm32f10x_md.s
#	$(AS) $(ASFLAGS) ./cmsis/startup_stm32f10x_md.s -o $(OBJDIR)/startup.o

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TM_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(HAL_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(FF_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(FF_SRC)/option/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(FF_SRC)/drivers/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC) : %.c : %.h $(INDEPENDENT_HEADERS)
	@touch $@

%.h: ;

$(BIN): $(OBJDIR) $(ALL_OBJ)
	$(CC) $(ALL_OBJ) $(LDFLAGS) -o $(BIN)
	$(CP) $(CPFLAGS) $(BIN) $(BIN).bin
	$(OD) $(ODFLAGS) $(BIN) > $(BIN).list
	$(SIZE) -B $(BIN)

clean:
	rm -f $(ALL_OBJ) $(BIN).map $(BIN) $(BIN).bin $(BIN).list
	rm -rf $(OBJDIR)

load: $(BIN)
	st-flash write $(BIN).bin 0x08000000


.PHONY: clean load
