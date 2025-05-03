#ifndef LEDBTN_H
#define LEDBTN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "microbit.h"

/* LED */
void leds_init(void);

/* Display */
extern uint8_t frame_buffer[LED_NUM_ROWS][LED_NUM_COLS];
void led_display(uint8_t pic[LED_NUM_ROWS][LED_NUM_COLS]);
void led_row_refresh(void);

/* Turn on/off and blink a specific LED for debugging. */
void led_on(int row, int col);
void led_off(int row, int col);
void led_blink(int row, int col);

/* Buttons */
void buttons_init(void);
uint32_t button_get(uint32_t button_idx);

/* Delay */
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* LEDBTN_H */
