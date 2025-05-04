#include "bsp/bsp.h"

int main() {
    int audio_freq = 1000;
    int ball_r = 0, ball_c = 0;
    int catch_r = 4, catch_c = 2;
    int ball_speed = 200, score = 0;

    bsp_init();

    printf("[START] Game of Catch!\n[INFO] Score: %d\n", score);
    audio_sweep(500, 2000, 100);
    timer_start(0, 5, led_row_refresh);

    while (1) {
        // Clear the previous position of the catch
        for (int c = 0; c < LED_NUM_COLS; c++) {
            frame_buffer[catch_r][c] = 0;
        }
        // Update the catch position based on button presses
        if (button_get(0)) {
            catch_c = (catch_c - 1 + LED_NUM_COLS) % LED_NUM_COLS;  // Move left
            frame_buffer[catch_r][catch_c] = 1;
            printf("[INFO] Catch moved left\n");
            audio_sweep(500, 2000, 50);
        }
        if (button_get(1)) {
            catch_c = (catch_c + 1) % LED_NUM_COLS;  // Move right
            frame_buffer[catch_r][catch_c] = 1;
            printf("[INFO] Catch moved right\n");
            audio_sweep(2000, 500, 50);
        }
        frame_buffer[catch_r][catch_c] = 1;
        timer_delay(50);

        frame_buffer[ball_r][ball_c] = 1;
        timer_delay(ball_speed);
#if 0  // Can get annoying during debugging
        audio_beep(audio_freq, 20);
#endif
        frame_buffer[ball_r][ball_c] = 0;

        ball_r++;
        audio_freq *= 1.1;
        if (ball_r == LED_NUM_ROWS) {
            // Ball reached the bottom
            audio_freq = 1000;
            // Reset ball position
            ball_r = 0;
            ball_c = (ball_c + 1) % LED_NUM_COLS;
        } else if (ball_r == catch_r && ball_c == catch_c) {
            // Collision detection
            audio_sweep(500, 2000, 50);
            if (ball_speed < 50)
                ball_speed = 50;  // Minimum speed
            else
                ball_speed -= 10;  // Increase speed
            // Reset ball position
            ball_r = 0;
            ball_c = (ball_c + 1) % LED_NUM_COLS;
            printf("[INFO] Catch successful! Score: %d\n", ++score);
        }
    }

    return 0;
}
