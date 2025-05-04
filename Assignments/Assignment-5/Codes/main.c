#include "bsp/bsp.h"
#include "os.h"

void task1(void) {
    while (1) {
        led_on(0, 0);
        led_off(0, 1);
        led_off(0, 2);
        task_yield();
    }
}

void task2(void) {
    while (1) {
        led_on(0, 1);
        led_off(0, 2);
        led_off(0, 0);
        task_yield();
    }
}

void task3(void) {
    while (1) {
        led_on(0, 2);
        led_off(0, 0);
        led_off(0, 1);
        task_yield();
    }
}

int main(void) {
    leds_init();

    task_create(task1);
    task_create(task2);
    task_create(task3);

    while (1) {
        task_yield();
    }
}
