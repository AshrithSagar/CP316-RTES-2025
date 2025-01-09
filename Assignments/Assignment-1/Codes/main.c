#include "microbit.h"
#include "myled.h"
#include "uart.h"

// .rodata
const int m = 7; // ROM
const int c = 5; // ROM

// .data
int x = 10; // initialized to to 10, but can later change later
            // x has to be in RAM, but value 10 should be in ROM
            // startup code copies initial values from ROM to RAM

// .bss
int y; // RAM
       // startup code initializes y to 0

int main() {
  y = m * x + c;

  uart_init(UART_RX, UART_TX);
  uart_puts("hello, world!\n");

  while (1) {
    led_on(2, 2);
    delay(1000); // some delay
    led_off(2, 2);
    delay(1000);
  }

  return 0;
}
