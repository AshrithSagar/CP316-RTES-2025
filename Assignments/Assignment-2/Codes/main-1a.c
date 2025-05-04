// Function-call and loop overheads, and clock cycles per iteration in delay()
// function.

#include "bsp.h"

#define SYSTICK_CVR (*(volatile unsigned long *)0xE000E018)

volatile unsigned int counter = 0;
volatile unsigned int ticks_taken_0 = 0;
volatile unsigned int ticks_taken_1 = 0;

void delay_ms(volatile int n) {
    while (n > 0) n--;
}

void measure() {
    volatile uint32_t start, end;

    // Function call overhead
    start = SYSTICK_CVR;
    delay_ms(0);
    end = SYSTICK_CVR;

    ticks_taken_0 += (start - end);
    // Since decrementing timer

    // Loop overhead
    start = SYSTICK_CVR;
    delay_ms(1);
    end = SYSTICK_CVR;

    ticks_taken_1 += (start - end);
    // Since decrementing timer

    counter++;
}

void show_averages() {
    if (counter > 0) {
        printf("\n\nFunction call overhead:");

        float time_taken = (float)ticks_taken_0 / 64;
        // In microseconds, since 64 MHz clock

        float average_time = (float)time_taken / (float)counter;

        printf(" Average: %f microseconds,", average_time);
        printf(" across %d iterations", counter);

        printf("\nLoop overhead:");

        time_taken = (float)(ticks_taken_1 - ticks_taken_0) / 64;
        // In microseconds, since 64 MHz clock

        average_time = (float)time_taken / (float)counter;

        printf(" Average: %f microseconds,", average_time);
        printf(" across %d iterations", counter);

        printf("\nClock cycles per iteration:");

        int clock_cycles = ticks_taken_1 / counter;

        printf(" %d clock cycles", clock_cycles);

        ticks_taken_0 = 0;
        counter = 0;
    }
}

int main() {
    uart_init(UART_RX, UART_TX);
    timer_init();

    timer_start(0, 1, measure);
    timer_start(1, 1000, show_averages);

    return 0;
}
