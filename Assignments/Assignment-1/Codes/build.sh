# Toolchain installed using homebrew; PATH is taken care

# ARM architecture specific compiler flags
CFLAGS="-mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16"

# Compile the source files
echo Compiling startup.c
arm-none-eabi-gcc -c $CFLAGS startup.c
echo Compiling system.c
arm-none-eabi-gcc -c $CFLAGS system.c
echo Compiling main.c
arm-none-eabi-gcc -c $CFLAGS main.c
echo Compiling uart.c
arm-none-eabi-gcc -c $CFLAGS uart.c

# Link the object code to form exectuable program
echo Linking
arm-none-eabi-ld -T bare.ld -Map tiny.map \
        startup.o system.o main.o uart.o -o tiny.out \

# Check sizes
arm-none-eabi-size tiny.out

# Generate HEX file to load on the target
echo Generating hex
arm-none-eabi-objcopy -O ihex tiny.out tiny.hex

# Upload on the target
cp tiny.hex /Volumes/MICROBIT
