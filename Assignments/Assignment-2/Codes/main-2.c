// Stopwatch

#include "bsp.h"

#define DEBOUNCE_DELAY 50  // In milliseconds

volatile uint32_t start = 0, end = 0, elapsed = 0;
volatile int button_state = 0;  // 0: Released, 1: Pressed, 2: Stopped

#define ROWS 5
#define COLS 5
volatile int current_r = 0, current_c = 0;
volatile int framebuffer[ROWS][COLS] = {
    {1, 0, 1, 0, 1},
    {0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1},
    {0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1},
};

void stopwatch() {
    static uint32_t last_press_time = 0;

    if (button_get(0)) {  // Button pressed
        if (button_state == 0 &&
            (timer_ticks - last_press_time) > DEBOUNCE_DELAY) {
            if (start == 0) {  // First press
                start = timer_ticks;
            } else {  // Second press
                end = timer_ticks;
                elapsed = end - start;
                button_state = 2;  // Mark as stopped
            }
            last_press_time = timer_ticks;
            button_state = 1;  // Mark button as pressed
        }
    } else {
        button_state = 0;  // Reset on release
    }
}

void print_stopwatch() {
    if (start != 0 && button_state == 1) {
        printf("\rTime: %f s", (float)(timer_ticks - start) / 1000.0);
    }
    if (button_state == 2) {
        printf("\nElapsed time: %f s\n", (float)elapsed / 1000.0);
    }
}

void display_refresh() {
    // Turn off previous LED
    led_off(current_r, current_c);

    // Move to next LED
    current_c++;
    if (current_c >= COLS) {
        current_c = 0;
        current_r = (current_r + 1) % ROWS;
    }

    // Turn on next LED if it's set in framebuffer
    if (framebuffer[current_r][current_c]) {
        led_on(current_r, current_c);
    }
}

int main() {
    uart_init(UART_RX, UART_TX);
    timer_init();

    printf("\nStopwatch: Hold button A to start/stop\n\r");

    timer_start(0, 10, stopwatch);
    // Check button every 10ms

    timer_start(1, 100, print_stopwatch);
    // Print every 100ms

    timer_start(2, 1, display_refresh);
    // Refresh display every 1ms
    // 1-2ms worked while testing. Anything greater than 3ms had more flicker,
    // and anything greater than 5ms was not persistent enough.
    // Toggling the LEDs every 1ms => 25ms for the entire display
    // => 40Hz refresh rate, which is good enough for the
    // human eye to be persistent.
    // 2ms would give 20Hz, which is almost close to the ~16Hz human threshold.

    return 0;
}
