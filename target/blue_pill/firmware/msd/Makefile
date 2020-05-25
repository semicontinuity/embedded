BIN=msd

OBJDIR=mk

TOOLS_PREFIX=arm-none-eabi-

CPFLAGS=-Obinary
ODFLAGS=-S

CFLAGS=-c -mcpu=cortex-m3 -mthumb -Wall -Werror -mapcs-frame -Os
#CFLAGS=-c -mcpu=cortex-m3 -mthumb -Wall -Werror -mapcs-frame -D__thumb2__=1 -Os
CFLAGS+=-msoft-float -gdwarf-2 -mno-sched-prolog -fno-hosted -mtune=cortex-m3
CFLAGS+=-march=armv7-m -mfix-cortex-m3-ldrd -ffunction-sections -fdata-sections
CFLAGS+=-I.
CFLAGS+=-DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER

LDFLAGS=-static -mcpu=cortex-m3 -mthumb -mthumb-interwork -Wl,--start-group
LDFLAGS+=-L$(TOOLS_PATH)/lib/thumb -lc -lg -lstdc++ -lsupc++ -lgcc -lm
#LDFLAGS+=-L$(TOOLS_PATH)/lib/thumb2 -lc -lg -lstdc++ -lsupc++ -lgcc -lm
LDFLAGS+=-Wl,--end-group -Xlinker -Map -Xlinker $(BIN).map -Xlinker
LDFLAGS+=-T ./stm32f100rb_flash.ld -o $(BIN)
LDFLAGS+=-Wl,--gc-sections -Wl,-s

ASFLAGS=-mcpu=cortex-m3 -I. -gdwarf-2 -gdwarf-2

CC=$(TOOLS_PREFIX)gcc
AS=$(TOOLS_PREFIX)as
SIZE=$(TOOLS_PREFIX)size
CP=$(TOOLS_PREFIX)objcopy
OD=$(TOOLS_PREFIX)objdump

# These are main project sources
SRC=$(wildcard *.c)
OBJ=$(addprefix $(OBJDIR)/, $(SRC:%.c=%.o))

ALL_OBJ=$(OBJ)
ALL_SRC=$(SRC)

all: $(BIN)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.h: ;

$(BIN): $(OBJDIR) $(ALL_OBJ)
	$(CC) $(ALL_OBJ) $(LDFLAGS)
	$(CP) $(CPFLAGS) $(BIN) $(BIN).bin
	$(OD) $(ODFLAGS) $(BIN) > $(BIN).list
	$(SIZE) -B $(BIN)

clean:
	rm -f $(ALL_OBJ) $(BIN).map $(BIN) $(BIN).list
	rm -rf $(OBJDIR)

load: $(BIN)
	st-flash write $(BIN).bin 0x08000000


.PHONY: clean load
