#include "bsp/myled.h"
#include "os.h"

#define FPCCR (*(volatile long*)0xE000EF34)

void task1(void) {
    led_on(2, 2);
    delay(1000);
    while (1) {
        task_yield();
        led_on(4, 4);
        delay(1000);
    }
}

int main(void) {
    led_on(0, 0);
    delay(1000);
    FPCCR &= ~(1 << 30);

    task_create(task1);
    led_on(1, 1);
    delay(1000);

    while (1) {
        task_yield();
        led_on(3, 3);
        delay(1000);
    }
}
