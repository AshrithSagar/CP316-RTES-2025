#include "bsp/bsp.h"

int main() {
    int audio_freq = 1000;
    int ball_r = 0, ball_c = 0;
    int catch_r = 4, catch_c = 2;

    bsp_init();

    uart_puts("[START] Game of Catch!\n");
    audio_sweep(500, 2000, 100);
    timer_start(0, 5, led_row_refresh);

    while (1) {
        frame_buffer[catch_r][catch_c] = 1;

        if (button_get(0)) audio_sweep(500, 2000, 200);

        if (button_get(1)) audio_sweep(2000, 500, 200);

        frame_buffer[ball_r][ball_c] = 1;
        timer_delay(200);
        frame_buffer[ball_r][ball_c] = 0;

        ball_r++;
        audio_freq *= 1.1;
        if (ball_r == LED_NUM_ROWS) {
            audio_freq = 1000;
            ball_r = 0;
            ball_c = (ball_c + 1) % LED_NUM_COLS;
        }
    }

    return 0;
}
