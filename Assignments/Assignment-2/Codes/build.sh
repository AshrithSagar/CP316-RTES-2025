# Toolchain installed using homebrew; $PATH is taken care

# ARM architecture specific compiler flags
CFLAGS="-O3 -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16"
LIBS="/opt/arm-gcc/arm-none-eabi/lib/thumb/v7e-m+fp/hard/libm.a \
/opt/arm-gcc/arm-none-eabi/lib/thumb/v7e-m+fp/hard/libc.a \
/opt/arm-gcc/lib/gcc/arm-none-eabi/14.2.1/thumb/v7e-m+fp/hard/libgcc.a"

# Compile the source files
echo Compiling startup.c
arm-none-eabi-gcc -c $CFLAGS startup.c
echo Compiling system.c
arm-none-eabi-gcc -c $CFLAGS system.c

echo Preprocessing main.c
arm-none-eabi-gcc -c $CFLAGS main.c

echo Compiling ledbtn.c
arm-none-eabi-gcc -c $CFLAGS ledbtn.c

echo Compiling uart.c
arm-none-eabi-gcc -c $CFLAGS uart.c

echo Compiling printf.c
arm-none-eabi-gcc -c $CFLAGS printf.c

echo Compiling timer.c
arm-none-eabi-gcc -c $CFLAGS timer.c

# Link the object code to form exectuable program
echo Linking
arm-none-eabi-ld -T bare.ld -Map tiny.map \
startup.o system.o main.o ledbtn.o uart.o printf.o timer.o $LIBS -o tiny.out

# Check sizes
arm-none-eabi-size tiny.out

# Generate HEX file to load on the target
echo Generating hex
arm-none-eabi-objcopy -O ihex tiny.out tiny.hex
# Takes out binary code, converts into hex (ASCII)

# Upload on the target
echo Flashing
cp tiny.hex /Volumes/MICROBIT
