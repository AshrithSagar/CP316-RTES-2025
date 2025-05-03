# Path to tool-chain
export PATH=$PATH:/opt/arm-gcc

# Compile the source files
echo Compiling gpio.c
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16 gpio.c
echo Compiling ledbtn.c
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16 ledbtn.c
echo Compiling uart.c
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16 uart.c
echo Compiling printf.c
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16 printf.c
echo Compiling pwm.c
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16 pwm.c
echo Compiling adc.c
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16 adc.c
echo Compiling audio.c
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16 audio.c
echo Compiling timer.c
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16 timer.c
echo Compiling bsp.c
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16 bsp.c

# Link the object code to form exectuable program
echo Generating libbsp.a
/bin/rm -f libbsp.a
arm-none-eabi-ar -r libbsp.a \
    gpio.o \
    ledbtn.o \
    uart.o \
    printf.o \
    pwm.o \
    adc.o \
    audio.o \
    timer.o \
    bsp.o

# We can remove the object files now
/bin/rm \
    gpio.o \
    ledbtn.o \
    uart.o \
    printf.o \
    pwm.o \
    adc.o \
    audio.o \
    timer.o \
    bsp.o
