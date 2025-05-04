#include "bsp/bsp.h"
#include "bsp/nrf52833.h"

volatile int n, prev_n;
volatile int r0, c0;

uint8_t get_random_byte() {
    NRF_RNG->EVENTS_VALRDY = 0;
    NRF_RNG->TASKS_START = 1;

    while (NRF_RNG->EVENTS_VALRDY == 0);  // Wait

    uint8_t value = NRF_RNG->VALUE;
    NRF_RNG->TASKS_STOP = 1;
    return value;
}

#define DEBOUNCE_TIME 20  // ms

void button0_press(void) {
    frame_buffer[r0][c0] = 0;
    if (c0 > 0) c0--;
    frame_buffer[r0][c0] = 1;

    n++;
}

int main() {
    int r, c;
    int n1;

    bsp_init();

    printf("button 0 is used with interrupts.\n");
    printf("button 1 is used with polling.\n");
    printf("\n");
    timer_start(0, 5, led_row_refresh);

    c = 2;
    r = 0;
    r0 = 4;
    c0 = 2;
    prev_n = n = 0;
    n1 = 0;

    gpio_inten(BUTTON_0, 0, GPIO_FALLINGEDGE, button0_press);

    while (1) {
        frame_buffer[r0][c0] = 1;

        if (button_get(1)) {
            frame_buffer[r0][c0] = 0;
            if (c0 < (LED_NUM_COLS - 1)) c0++;
            frame_buffer[r0][c0] = 1;
            n1++;
            printf("n1 = %d\n", n1);
        }

        if (n != prev_n) {
            printf("n0 = %d\n", n);
            prev_n = n;
        }

        frame_buffer[r][c] = 1;
        timer_delay(400);
        frame_buffer[r][c] = 0;

        r++;
        if (r == LED_NUM_ROWS) r = 0;
    }

    return 0;
}
