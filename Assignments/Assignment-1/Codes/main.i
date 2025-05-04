# 0 "main.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "main.c"
# 1 "microbit.h" 1
# 2 "main.c" 2
# 1 "myled.h" 1
# 18 "myled.h"
static const unsigned char led_rows[] = {21, 22, 15, 24, 19};
static const unsigned char led_cols[] = {28, 11, 31, 37, 30};

static inline void gpio_set(int pin) {
    unsigned long baseaddr;

    baseaddr = (((pin) < 32) ? (0x50000000UL) : (0x50000300UL));
    pin = (((pin) < 32) ? (pin) : (pin - 32));

    (*((volatile long *)(baseaddr + 0x514))) |= (1 << pin);
    (*((volatile long *)(baseaddr + 0x508))) = (1 << pin);
}

static inline void gpio_clear(int pin) {
    unsigned long baseaddr;

    baseaddr = (((pin) < 32) ? (0x50000000UL) : (0x50000300UL));
    pin = (((pin) < 32) ? (pin) : (pin - 32));

    (*((volatile long *)(baseaddr + 0x514))) |= (1 << pin);
    (*((volatile long *)(baseaddr + 0x50c))) = (1 << pin);
}

static inline void led_on(int r, int c) {
    gpio_set(led_rows[r]);
    gpio_clear(led_cols[c]);
}

static inline void led_off(int r, int c) {
    gpio_clear(led_rows[r]);
    gpio_set(led_cols[c]);
}

static inline void delay(volatile int n) {
    n *= 1000;
    while (n > 0) n--;
}

static inline void led_blink(int r, int c) {
    while (1) {
        led_on(r, c);
        delay(1000);
        led_off(r, c);
        delay(1000);
    }
}
# 3 "main.c" 2
# 1 "uart.h" 1



# 1 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/lib/gcc/arm-none-eabi/14.2.1/include/stdint.h" 1 3 4
# 9 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/lib/gcc/arm-none-eabi/14.2.1/include/stdint.h" 3 4
# 1 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/stdint.h" 1 3 4
# 12 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/stdint.h" 3 4
# 1 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/machine/_default_types.h" 1 3 4







# 1 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/sys/features.h" 1 3 4
# 28 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/sys/features.h" 3 4
# 1 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/_newlib_version.h" 1 3 4
# 29 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/sys/features.h" 2 3 4
# 9 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/machine/_default_types.h" 2 3 4
# 41 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/machine/_default_types.h" 3 4

# 41 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef signed char __int8_t;

typedef unsigned char __uint8_t;
# 55 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef short int __int16_t;

typedef short unsigned int __uint16_t;
# 77 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef long int __int32_t;

typedef long unsigned int __uint32_t;
# 103 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef long long int __int64_t;

typedef long long unsigned int __uint64_t;
# 134 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef signed char __int_least8_t;

typedef unsigned char __uint_least8_t;
# 160 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef short int __int_least16_t;

typedef short unsigned int __uint_least16_t;
# 182 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef long int __int_least32_t;

typedef long unsigned int __uint_least32_t;
# 200 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef long long int __int_least64_t;

typedef long long unsigned int __uint_least64_t;
# 214 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef long long int __intmax_t;







typedef long long unsigned int __uintmax_t;







typedef int __intptr_t;

typedef unsigned int __uintptr_t;
# 13 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/stdint.h" 2 3 4
# 1 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/sys/_intsup.h" 1 3 4
# 35 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/sys/_intsup.h" 3 4
       
       
       
       
       
       
       
       
# 190 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/sys/_intsup.h" 3 4
       
       
       
       
       
       
       
       
# 14 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/stdint.h" 2 3 4
# 1 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/sys/_stdint.h" 1 3 4
# 20 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/sys/_stdint.h" 3 4
typedef __int8_t int8_t ;



typedef __uint8_t uint8_t ;







typedef __int16_t int16_t ;



typedef __uint16_t uint16_t ;







typedef __int32_t int32_t ;



typedef __uint32_t uint32_t ;







typedef __int64_t int64_t ;



typedef __uint64_t uint64_t ;






typedef __intmax_t intmax_t;




typedef __uintmax_t uintmax_t;




typedef __intptr_t intptr_t;




typedef __uintptr_t uintptr_t;
# 15 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/stdint.h" 2 3 4






typedef __int_least8_t int_least8_t;
typedef __uint_least8_t uint_least8_t;




typedef __int_least16_t int_least16_t;
typedef __uint_least16_t uint_least16_t;




typedef __int_least32_t int_least32_t;
typedef __uint_least32_t uint_least32_t;




typedef __int_least64_t int_least64_t;
typedef __uint_least64_t uint_least64_t;
# 51 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/stdint.h" 3 4
  typedef int int_fast8_t;
  typedef unsigned int uint_fast8_t;
# 61 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/stdint.h" 3 4
  typedef int int_fast16_t;
  typedef unsigned int uint_fast16_t;
# 71 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/stdint.h" 3 4
  typedef int int_fast32_t;
  typedef unsigned int uint_fast32_t;
# 81 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/arm-none-eabi/include/stdint.h" 3 4
  typedef long long int int_fast64_t;
  typedef long long unsigned int uint_fast64_t;
# 10 "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/lib/gcc/arm-none-eabi/14.2.1/include/stdint.h" 2 3 4
# 5 "uart.h" 2


# 6 "uart.h"
extern void uart_init(uint32_t rxpin, uint32_t txpin);
extern void uart_putc(char ch);
extern void uart_puts(char s[]);
# 4 "main.c" 2


const int m = 7;
const int c = 5;


int x = 10;




int y;


int main() {
    y = m * x + c;

    uart_init(40, 6);
    uart_puts("hello, world!\n");

    while (1) {
        led_on(2, 2);
        delay(1000);
        led_off(2, 2);
        delay(1000);
    }

    return 0;
}
