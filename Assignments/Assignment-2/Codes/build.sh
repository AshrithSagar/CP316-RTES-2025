# Toolchain installed using homebrew; $PATH is taken care

# Usage: ./build.sh /dev/diskX main-*.c
# args: mount point, and main-*.c is the file to be compiled
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <mount-point> <main-file>"
    exit 1
fi

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

# Provide a main.c file as argument
echo Preprocessing "$2"
arm-none-eabi-gcc -c $CFLAGS "$2"

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
    startup.o system.o "${2%.c}.o" ledbtn.o uart.o printf.o timer.o $LIBS -o tiny.out

# Check sizes
arm-none-eabi-size tiny.out

# Generate HEX file to load on the target
echo Generating hex
arm-none-eabi-objcopy -O ihex tiny.out tiny.hex
# Takes out binary code, converts into hex (ASCII)

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
