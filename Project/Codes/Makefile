TARGET = MICROBIT

# Source files
SRC = startup.c system.c main.c motor_task.c

# Object files generated from the source files
OBJ = $(subst .c,.o,$(SRC))

# Include directories
CFLAGS = -I bsp -Ibsp2 -I rtx  # library include path | Where to pick up the decleration/APIs
LINKER_SCRIPT = nrf52833.ld        # linker command script

all: flash

########################################################################
include rules.mk
########################################################################

# Libraries used
LIBS = bsp/libbsp.a bsp2/libbsp2.a rtx/librtx.a #Where to pick up the definations

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
	@make --no-print-directory -C bsp2 libbsp2.a
	@make --no-print-directory -C rtx librtx.a

$(TARGET).out:: $(OBJ) $(LINKER_SCRIPT) bsp/libbsp.a
	$(LD) $(LDFLAGS) $(OBJ) $(LIBS) -o $@
	$(SIZE) $@

clean::
	cd bsp && make clean
	cd bsp2 && make clean
	cd rtx && make clean
	/bin/rm -f $(OBJ) system.map $(TARGET).out $(TARGET).hex

.PHONY: all flash clean

startup.o: startup.c  # Vector table and CRT initialization
system.o: system.c  # Clock initialization
main.o: main.c bsp/bsp.h bsp/adc.h bsp/audio.h bsp/gpio.h bsp/ledbtn.h \
 bsp/microbit.h bsp/printf.h bsp/pwm.h bsp/uart.h rtx/cmsis_os2.h
motor_task.o: motor_task.c bsp/bsp.h bsp/adc.h bsp/audio.h bsp/gpio.h \
 bsp/ledbtn.h bsp/microbit.h bsp/printf.h bsp/pwm.h bsp/uart.h \
 bsp/microbit.h bsp2/bsp2.h bsp2/encoder.h bsp2/i2c.h bsp2/lsm303agr.h \
 bsp2/motor.h bsp2/radio.h rtx/cmsis_os2.h
