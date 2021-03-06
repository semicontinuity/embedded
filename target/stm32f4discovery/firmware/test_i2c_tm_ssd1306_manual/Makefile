BIN=test_i2c_tm_ssd1306_manual

# Headers that don't have c-files with same name
#  but project depends on them
INDEPENDENT_HEADERS=defines.h


TM=

TM+=tm_stm32_disco
TM+=tm_stm32_delay
TM+=tm_stm32_i2c
TM+=tm_stm32_ssd1306
TM+=tm_stm32_gpio
TM+=tm_stm32_rcc
TM+=tm_stm32_fonts


TM_DIR?=/opt/stm32fxxx_hal_libraries/00-STM32_LIBRARIES
TM_SRC?=$(TM_DIR)
TM_INC?=$(TM_DIR)
TM_LIBOBJ=$(addprefix $(OBJDIR)/, $(addsuffix .o, $(TM)))


HAL=
HAL+=stm32f4xx_hal
HAL+=stm32f4xx_hal_cortex
HAL+=stm32f4xx_hal_gpio
HAL+=stm32f4xx_hal_rcc
HAL+=stm32f4xx_hal_i2c

HAL_DIR?=/opt/stm32fxxx_hal_libraries/00-HAL_DRIVERS/STM32F4xx_HAL_Driver
HAL_SRC?=$(HAL_DIR)/Src
HAL_INC?=$(HAL_DIR)/Inc
HAL_LIBSRC=$(addprefix $(HAL_SRC)/, $(addsuffix .c, $(HAL)))
HAL_LIBOBJ=$(addprefix $(OBJDIR)/, $(addsuffix .o, $(HAL)))


CMSIS?=/opt/stm32fxxx_hal_libraries/00-HAL_DRIVERS/CMSIS
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

CFLAGS+=-DSTM32F407xx -DSTM32F4xx -DSTM32F4_DISCOVERY

# default linker flags
LD_FILE=/opt/stm32fxxx_hal_libraries/01-STM32Fxxx_SW4STM32_CMSIS_Default_Project/LinkerScript.ld
LDFLAGS += -T $(LD_FILE) -mthumb -u _start -Xlinker -M -Xlinker -Map=$(BIN).map
LDFLAGS += -Wl,--gc-section


ASFLAGS=-mcpu=cortex-m4

CC=$(TOOLS_PREFIX)gcc
AS=$(TOOLS_PREFIX)as
SIZE=$(TOOLS_PREFIX)size
CP=$(TOOLS_PREFIX)objcopy
OD=$(TOOLS_PREFIX)objdump

# These are main project sources
SRC=$(wildcard *.c)
MAIN_OBJ=$(addprefix $(OBJDIR)/, $(SRC:%.c=%.o))

OBJ=
OBJ+=$(OBJDIR)/startup.o
ALL_OBJ=$(OBJ) $(MAIN_OBJ) $(TM_LIBOBJ) $(HAL_LIBOBJ)

all: $(BIN)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/startup.o: $(CMSIS__SRC)/Templates/gcc/startup_stm32f407xx.s
	$(AS) $(ASFLAGS) $(CMSIS__SRC)/Templates/gcc/startup_stm32f407xx.s -o $(OBJDIR)/startup.o


$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TM_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(HAL_SRC)/%.c
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
