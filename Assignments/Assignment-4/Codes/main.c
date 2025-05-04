#include "bsp/bsp.h"
#include "bsp/nrf52833.h"

#define DEBOUNCE_TIME 20  // ms

// Global variables
volatile int button0_count, prev_button0_count;
volatile int catch_r, catch_c;

uint8_t get_random_byte() {
    NRF_RNG->EVENTS_VALRDY = 0;
    NRF_RNG->TASKS_START = 1;

    while (NRF_RNG->EVENTS_VALRDY == 0);  // Wait

    uint8_t value = NRF_RNG->VALUE;
    NRF_RNG->TASKS_STOP = 1;
    return value;
}

void button0_press(void) {
    frame_buffer[catch_r][catch_c] = 0;
    catch_c = (catch_c - 1 + LED_NUM_COLS) % LED_NUM_COLS;  // Move left
    frame_buffer[catch_r][catch_c] = 1;
    button0_count++;
}

int main() {
    // Local variables
    int audio_freq = 1000;
    int ball_speed = 200, score = 0;
    int ball_r, ball_c;
    int button1_count;

    bsp_init();

    printf("\n");
    printf("[START] Game of Catch!\n");
    printf("[DEBUG] Button 0 is used with interrupts.\n");
    printf("[DEBUG] Button 1 is used with polling.\n");
    audio_sweep(500, 2000, 100);
    timer_start(0, 5, led_row_refresh);

    ball_c = 0, ball_r = 0;
    catch_r = 4, catch_c = 2;
    button0_count = button1_count = prev_button0_count = 0;

    gpio_inten(BUTTON_0, 0, GPIO_FALLINGEDGE, button0_press);

    while (1) {
        frame_buffer[catch_r][catch_c] = 1;

        if (button_get(1)) {
            frame_buffer[catch_r][catch_c] = 0;
            catch_c = (catch_c + 1) % LED_NUM_COLS;  // Move right
            frame_buffer[catch_r][catch_c] = 1;
            printf("[DEBUG] Button 1 count = %d\n", ++button1_count);
            printf("[INFO] Catch moved left\n");
            audio_sweep(500, 2000, 50);
        }

        // Keep ISR's short, so `printf` here
        if (button0_count != prev_button0_count) {
            printf("[DEBUG] Button 0 count = %d\n", button0_count);
            printf("[INFO] Catch moved right\n");
            audio_sweep(2000, 500, 50);
            prev_button0_count = button0_count;
        }

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
            ball_c = get_random_byte() % LED_NUM_COLS;
            printf("[INFO] Ball missed! Score: %d\n", score);
            printf("[INFO] New ball in column %d\n", ball_c);
        } else if (ball_r == catch_r && ball_c == catch_c) {
            // Collision detected
            audio_sweep(500, 2000, 250);
            if (ball_speed < 50)
                ball_speed = 50;  // Minimum speed
            else
                ball_speed -= 10;  // Increase speed
            // Reset ball position
            ball_r = 0;
            ball_c = get_random_byte() % LED_NUM_COLS;
            printf("[INFO] Catch successful! Score: %d\n", ++score);
            printf("[INFO] New ball in column %d\n", ball_c);
        }
    }

    return 0;
}
