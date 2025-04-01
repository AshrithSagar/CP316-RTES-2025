#include "bsp/bsp.h"
#include "rtx/cmsis_os2.h"

void led_callback(void *arg) {
  (void)arg;
  led_row_refresh();
}

void app_main(void *arg) {
  int r, c;
  int f;
  osTimerId_t timer_id;

  osTimerNew(led_callback, osTimerPeriodic, NULL, NULL);
  osTimerStart(timer_id, 5);

  frame_buffer[4][2] = 1;

  c = 0;
  r = 0;
  f = 1000;
  while (1) {
    if (button_get(0))
      audio_sweep(500, 2000, 200);

    if (button_get(1))
      audio_sweep(2000, 500, 200);

    frame_buffer[r][c] = 1;
    osDelay(200);
    // audio_beep(f, 20);
    frame_buffer[r][c] = 0;

    r++;
    f *= 1.1;
    if (r == LED_NUM_ROWS) {
      f = 1000;
      r = 0;
    }
  }
}

int main(void) {
  bsp_init();
  uart_puts("hello, world!\n");
  audio_sweep(500, 2000, 100);

  osKernelInitialize();
  osThreadNew(app_main, NULL, NULL);
  osKernelStart();

  // never returns
  return 0;
}
