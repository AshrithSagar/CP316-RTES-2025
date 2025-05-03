GCCARM=/opt/arm-gcc
CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld
AR=arm-none-eabi-ar
OBJCOPY=arm-none-eabi-objcopy
SIZE=arm-none-eabi-size

# C flags common to all targets
CFLAGS += -mcpu=cortex-m4 -mthumb -mabi=aapcs   # architecture-specific
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16    # floating point unit

# Assembler flags for architecture-specific code
SFLAGS += -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16


.SUFFIXES: .c .i .S .s .o

.c.o:   # compile and assemble
	$(CC) -c $(CFLAGS) $< -o $@

.c.i:   # preprocess
	$(CC) -E $(CFLAGS) $< > $@

.c.S:   # only cross-compile
	$(CC) -S $(CFLAGS) $< -o $@

.S.i:   # preprocess asm code
	$(CC) -E $(CFLAGS) $< > $@

.S.o:   # preprocess and assemble
	$(CC) -c $(SFLAGS) $< -o $@

.s.o:   # assemble
	$(AS) -c $(SFLAGS) $< -o $@

$(LIB): $(OBJ)
	/bin/rm -f $@
	$(AR) -r $@ $(OBJ)

clean::
	/bin/rm -f $(OBJ) $(LIB)

depend: # generate dependencies
	@$(CC) -MM $(CFLAGS) $(SRC)
