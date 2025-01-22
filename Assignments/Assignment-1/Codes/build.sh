# Toolchain installed using homebrew; $PATH is taken care

# ARM architecture specific compiler flags
CFLAGS="-mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16"
# -mcpu=cortex-m4: Target CPU architecture
# -mthumb: Thumb instruction set
# -mabi=aapcs: Uses the ARM Architecture Procedure Call Standard (AAPCS) for the application binary interface
# -mfloat-abi=hard: Uses hardware floating-point instructions
# -mfpu=fpv4-sp-d16: Specifies the floating-point unit as FPv4 with single-precision and 16 registers

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
arm-none-eabi-ld -T bare.ld -Map tiny.map startup.o system.o main.o uart.o -o tiny.out

# Check sizes
arm-none-eabi-size tiny.out

# Generate HEX file to load on the target
echo Generating hex
arm-none-eabi-objcopy -O ihex tiny.out tiny.hex

# Upload on the target
# Check with `df -ahY` to see the mounted devices,
# and pass the correct one as argument while running
# Eg: `sudo ./build.sh /dev/disk6`
echo Flashing
FLASHDIR="/Volumes/MICROBIT"
mkdir -p "$FLASHDIR"
diskutil unmount "$1"
sudo mount -t msdos "$1" "$FLASHDIR"
cp tiny.hex "$FLASHDIR"
