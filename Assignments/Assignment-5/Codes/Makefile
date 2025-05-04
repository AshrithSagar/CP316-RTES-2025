TARGET = MICROBIT

SRC = startup.c system.c main.c os.c
ASM = syscall.s
OBJ = $(subst .c,.o,$(SRC))
OBJ += $(subst .s,.o,$(ASM))
CFLAGS = -I bsp # library include path
LINKER_SCRIPT = nrf52833.ld        # linker command script

all: flash

########################################################################
include rules.mk
########################################################################

# Libraries used
LIBS = bsp/libbsp.a

# Add standard libraries at the very end of the linker input, after all objects
# that may need symbols provided by these libraries.
LIBS += $(GCCARM)/arm-none-eabi/lib/thumb/v7e-m+fp/hard/libm.a
LIBS += $(GCCARM)/arm-none-eabi/lib/thumb/v7e-m+fp/hard/libc.a
LIBS += $(GCCARM)/lib/gcc/arm-none-eabi/14.2.1/thumb/v7e-m+fp/hard/libgcc.a

LDFLAGS = -T $(LINKER_SCRIPT) -Map system.map --entry Reset_Handler

#########################################
# Auto detect platform and flash
# To override the default FLASHDIR, use: `make flash FLASHDIR=/path/to/flash`

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	IS_WSL := $(shell grep -qi microsoft /proc/version 2>/dev/null && echo 1 || echo 0)
	ifeq ($(IS_WSL),1) # WSL
		FLASHDIR ?= /mnt/c/Temp
	else # Native Linux
		FLASHDIR ?= /mnt/$(TARGET)
	endif
else ifeq ($(UNAME_S),Darwin) # macOS
	FLASHDIR ?= /Volumes/$(TARGET)
endif

flash: $(TARGET).hex
ifeq ($(UNAME_S),Linux)
ifeq ($(IS_WSL),1) # WSL
	/bin/cp $(TARGET).hex "$(FLASHDIR)"
	(cd "$(FLASHDIR)" && cmd.exe /c copy $(TARGET).hex E:)
else # Native Linux
	@if [ -d "$(FLASHDIR)" ]; then \
		/bin/cp $(TARGET).hex "$(FLASHDIR)"; \
		echo "Flashed to $(TARGET)"; \
	else \
		echo "Flash failed: Mount not found at $(FLASHDIR)"; \
	fi
endif
else ifeq ($(UNAME_S),Darwin) # macOS
	@if [ -d "$(FLASHDIR)" ]; then \
		/bin/cp $(TARGET).hex "$(FLASHDIR)"; \
		echo "Flashed to $(TARGET)"; \
	else \
		echo "Flash failed: Mount not found at $(FLASHDIR)"; \
	fi
else # Fallback
	@echo "Unknown platform: $(UNAME_S)"
	@exit 1
endif

#########################################

$(TARGET).hex: $(TARGET).out
	$(OBJCOPY) -O ihex $< $@

$(TARGET).out::
	@make --no-print-directory -C bsp libbsp.a

$(TARGET).out:: $(OBJ) $(LINKER_SCRIPT) bsp/libbsp.a
	$(LD) $(LDFLAGS) $(OBJ) $(LIBS) -o $@
	$(SIZE) $@

clean:
	cd bsp && make clean
	/bin/rm -f $(OBJ) system.map $(TARGET).out $(TARGET).hex

.PHONY: all flash clean

startup.o: startup.c
system.o: system.c
main.o: main.c bsp/myled.h os.h
os.o: os.c os.h
