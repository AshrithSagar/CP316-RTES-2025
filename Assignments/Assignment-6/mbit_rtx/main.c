#include "bsp/bsp.h"
#include "rtx/cmsis_os2.h"

void led_callback(void *arg) {
    (void)arg;
    led_row_refresh();
}

void thread_led(void *arg) {
    int r = 0, c = 0, f = 1000;
    frame_buffer[4][2] = 1;

    while (1) {
        frame_buffer[r][c] = 1;
        osDelay(200);
        frame_buffer[r][c] = 0;

        r++;
        f *= 1.1;
        if (r == LED_NUM_ROWS) {
            f = 1000;
            r = 0;
        }
    }
}

void thread_button(void *arg) {
    while (1) {
        if (button_get(0)) audio_sweep(500, 2000, 200);
        if (button_get(1)) audio_sweep(2000, 500, 200);
        osDelay(100);
    }
}

void thread_debug(void *arg) {
    while (1) {
        uart_puts("[DEBUG] This part runs in an other thread!\n");
        osDelay(1000);
    }
}

void app_main(void *arg) {
    osTimerId_t timer_id;
    timer_id = osTimerNew(led_callback, osTimerPeriodic, NULL, NULL);
    osTimerStart(timer_id, 5);

    osThreadNew(thread_led, NULL, NULL);
    osThreadNew(thread_button, NULL, NULL);
    osThreadNew(thread_debug, NULL, NULL);
}

int main(void) {
    bsp_init();
    uart_puts("[START] Hello world!\n");
    audio_sweep(500, 2000, 100);

    osKernelInitialize();
    osThreadNew(app_main, NULL, NULL);
    osKernelStart();

    // never returns
    return 0;
}
