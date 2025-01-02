# Path to tool-chain
export PATH=$PATH:/opt/arm-gcc/bin

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
# cmd.exe /c copy 'tiny.hex' E:

# If you're working in a WSL directory not visible to Windows, you
# will have to copy tiny.hex via some Windows folfer. For example:

# mkdir -p /mnt/c/Temp
/bin/rm -f /mnt/c/Temp/tiny.hex
/bin/cp tiny.hex /mnt/c/Temp
cd /mnt/c/Temp
cmd.exe /c copy tiny.hex E:
cd -

# The above command is applicable for a Windows PC. You may change it
# appropriately to on Linux or MacOS. It should be something like:
# cp tiny.hex /media/MICROBIT       # linux
# cp tiny.hex /Volumes/MICROBIT     # mac
