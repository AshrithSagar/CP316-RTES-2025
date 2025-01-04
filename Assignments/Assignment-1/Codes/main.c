#include "microbit.h"
#include "uart.h"
#include "myled.h"

// .rodata
const int m = 7;    // rom
const int c = 5;    // rom

// .data
int x = 10;     // initialized to to 10, but can later change later
                // x has to be in ram, but value 10 should be in rom
                // startup code copies initial values from rom to ram

// .bss
int y;          // ram
                // startup code initializes y to 0

int main ()
{
    y = m * x + c;

    uart_init(UART_RX, UART_TX);
    uart_puts("hello, world!\n");

    while (1)
    {
        led_on(2, 2);
        delay(1000);    // some delay
        led_off(2, 2);
        delay(1000);
    }

    return 0;
}
