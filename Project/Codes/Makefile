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

flash: $(TARGET).hex
	cp $(TARGET).hex /mnt/c/Temp
	(cd /mnt/c/Temp && cmd.exe /c copy $(TARGET).hex E:)

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

startup.o: startup.c #Vector table and crt initialization
system.o: system.c #clock initialization
main.o: main.c bsp/bsp.h rtx/cmsis_os2.h 
