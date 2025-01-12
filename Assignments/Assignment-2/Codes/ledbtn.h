#ifndef LEDBTN_H
#define LEDBTN_H

void gpio_set(int pin);
void gpio_clear(int pin);
void led_on(int r, int c);
void led_off(int r, int c);
void delay(volatile int n);
void led_blink(int r, int c);

// return 1 if button is pressed, 0 otherwise
// n = button ID, 0 for button A, 1 for button B
extern int button_get(int n);

#endif  /* LEDBTN_H */
