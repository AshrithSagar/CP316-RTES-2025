# Path to tool-chain
ARMGCC=/opt/arm-gcc
export PATH=$PATH:$ARMGCC/bin

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
cp MICROBIT.hex /mnt/c/Users/vdars/Temp
cd /mnt/c/Users/vdars/Temp
cmd.exe /c copy MICROBIT.hex E:
# (Windows CMD.EXE does not support UNC paths. Hence, copying into a
#  native Windows directory accessible to CMD.exe.
#  If you're working on a native Windows directory, you can directly
#  copy the hex file to Microbit drive.)

# The above command is applicable for a Windows PC. You may change it
# appropriately to on Linux or MacOS. It should be something like:
# cp MICROBIT.hex /media/MICROBIT       # linux
# cp MICROBIT.hex /Volumes/MICROBIT     # mac
