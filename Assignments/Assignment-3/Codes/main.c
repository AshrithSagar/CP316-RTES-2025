#include "bsp/bsp.h"

int main() {
    int r, c;
    int f;

    bsp_init();

    uart_puts("hello, world!\n");
    audio_sweep(500, 2000, 100);
    timer_start(0, 5, led_row_refresh);

    frame_buffer[4][2] = 1;

    c = 0;
    r = 0;
    f = 1000;
    while (1) {
        frame_buffer[4][2] = 1;

        if (button_get(0)) audio_sweep(500, 2000, 200);

        if (button_get(1)) audio_sweep(2000, 500, 200);

        frame_buffer[r][c] = 1;
        timer_delay(200);
#if 0  // can get annoying during debugging
        audio_beep(f, 20);
#endif
        frame_buffer[r][c] = 0;

        r++;
        f *= 1.1;
        if (r == LED_NUM_ROWS) {
            f = 1000;
            r = 0;
            c = (c + 1) % LED_NUM_COLS;
        }
    }

    return 0;
}
