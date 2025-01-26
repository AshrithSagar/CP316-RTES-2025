# ARM architecture specific compiler flags
CFLAGS="-Ibsp -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16"

# Compile the source files
echo Compiling startup.c
arm-none-eabi-gcc -c $CFLAGS startup.c

echo Compiling system.c
arm-none-eabi-gcc -c $CFLAGS system.c

echo Compiling main.c
arm-none-eabi-gcc -c $CFLAGS main.c

# Link the object code to form exectuable program
echo Linking MICROBIT.out
arm-none-eabi-ld -T nrf52833.ld -Map system.map --entry Reset_Handler \
startup.o system.o main.o bsp/libbsp.a \
$ARMGCC/arm-none-eabi/lib/thumb/v7e-m+fp/hard/libm.a \
$ARMGCC/arm-none-eabi/lib/thumb/v7e-m+fp/hard/libc.a \
$ARMGCC/lib/gcc/arm-none-eabi/14.2.1/thumb/v7e-m+fp/hard/libgcc.a \
-o MICROBIT.out

# Check sizes
arm-none-eabi-size MICROBIT.out

# Generate HEX file to load on the target
arm-none-eabi-objcopy -O ihex MICROBIT.out MICROBIT.hex

# Upload on the target
# echo Flashing
# sudo mkdir -p /mnt/MICROBIT
# sudo mount -t drvfs E: /mnt/MICROBIT
# sudo /bin/cp MICROBIT.hex /mnt/MICROBIT

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
