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
  while (n > 0)
    n--;
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



# 1 "/opt/homebrew/Cellar/arm-none-eabi-gcc/14.2.0/lib/gcc/arm-none-eabi/14.2.0/include/stdint.h" 1 3 4
# 9 "/opt/homebrew/Cellar/arm-none-eabi-gcc/14.2.0/lib/gcc/arm-none-eabi/14.2.0/include/stdint.h" 3 4
# 1 "/opt/homebrew/Cellar/arm-none-eabi-gcc/14.2.0/lib/gcc/arm-none-eabi/14.2.0/include/stdint-gcc.h" 1 3 4
# 34 "/opt/homebrew/Cellar/arm-none-eabi-gcc/14.2.0/lib/gcc/arm-none-eabi/14.2.0/include/stdint-gcc.h" 3 4

# 34 "/opt/homebrew/Cellar/arm-none-eabi-gcc/14.2.0/lib/gcc/arm-none-eabi/14.2.0/include/stdint-gcc.h" 3 4
typedef signed char int8_t;


typedef short int int16_t;


typedef long int int32_t;


typedef long long int int64_t;


typedef unsigned char uint8_t;


typedef short unsigned int uint16_t;


typedef long unsigned int uint32_t;


typedef long long unsigned int uint64_t;




typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef long int int_least32_t;
typedef long long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef short unsigned int uint_least16_t;
typedef long unsigned int uint_least32_t;
typedef long long unsigned int uint_least64_t;



typedef int int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;
typedef long long int int_fast64_t;
typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef long long unsigned int uint_fast64_t;




typedef int intptr_t;


typedef unsigned int uintptr_t;




typedef long long int intmax_t;
typedef long long unsigned int uintmax_t;
# 10 "/opt/homebrew/Cellar/arm-none-eabi-gcc/14.2.0/lib/gcc/arm-none-eabi/14.2.0/include/stdint.h" 2 3 4
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
