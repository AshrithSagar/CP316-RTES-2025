#include "bsp/myled.h"
#include "os.h"

#define FPCCR (*(volatile long*)0xE000EF34)
#define CSR (*(volatile long*)0xE000E010)
#define RVR (*(volatile long*)0xE000E014)
#define CVR (*(volatile long*)0xE000E018)

static inline void led_blink_with_delay(int r, int c, int delay_ms) {
    while (1) {
        led_on(r, c);
        delay(delay_ms);
        led_off(r, c);
        delay(delay_ms);
    }
}

void task1(void) {
    led_blink_with_delay(0, 0, 500);  // Top-left LED
}

void task2(void) {
    led_blink_with_delay(2, 2, 500);  // Center LED
}

void task3(void) {
    led_blink_with_delay(4, 4, 500);  // Bottom-right LED
}

int main(void) {
    FPCCR &= ~(1 << 30);

    task_create(task1);
    task_create(task2);
    task_create(task3);

    RVR = (64000000 / 1000) * 1000;  // 1 second
    CSR = 7;                         // Internal clock; Tick int, Enable

    while (1);  // Idle loop
}
