TARGET = MICROBIT

# Usage: make flash MOUNT_POINT=/dev/diskX
ifndef MOUNT_POINT
$(error MOUNT_POINT is not set. Usage: make flash MOUNT_POINT=/dev/diskX)
endif

# Source files
SRC = startup.c system.c main.c

# Object files generated from the source files
OBJ = $(subst .c,.o,$(SRC))

# Include directories
CFLAGS = -I bsp -I rtx # library include path
LINKER_SCRIPT = nrf52833.ld        # linker command script

all: flash

########################################################################
include rules.mk
########################################################################

# Libraries used
LIBS = bsp/libbsp.a rtx/librtx.a

# Add standard libraries at the very end of the linker input, after all objects
# that may need symbols provided by these libraries.
LIBS += $(GCCARM)/arm-none-eabi/lib/thumb/v7e-m+fp/hard/libm.a
LIBS += $(GCCARM)/arm-none-eabi/lib/thumb/v7e-m+fp/hard/libc.a
LIBS += $(GCCARM)/lib/gcc/arm-none-eabi/14.2.1/thumb/v7e-m+fp/hard/libgcc.a

LDFLAGS = -T $(LINKER_SCRIPT) -Map system.map --entry Reset_Handler

flash: $(TARGET).hex
	FLASHDIR="/Volumes/MICROBIT"
	sudo mkdir -p "$FLASHDIR"
	sudo mount -t msdos $(MOUNT_POINT) "$FLASHDIR"
	sudo /bin/cp $(TARGET).hex "$FLASHDIR"
	diskutil unmount "$FLASHDIR"

$(TARGET).hex: $(TARGET).out
	$(OBJCOPY) -O ihex $< $@

$(TARGET).out::
	@make --no-print-directory -C bsp libbsp.a
	@make --no-print-directory -C rtx librtx.a

$(TARGET).out:: $(OBJ) $(LINKER_SCRIPT) bsp/libbsp.a
	$(LD) $(LDFLAGS) $(OBJ) $(LIBS) -o $@
	$(SIZE) $@

clean::
	cd bsp && make clean
	cd rtx && make clean
	/bin/rm -f $(OBJ) system.map $(TARGET).out $(TARGET).hex

.PHONY: all flash clean

startup.o: startup.c
system.o: system.c
main.o: main.c bsp/bsp.h rtx/cmsis_os2.h
