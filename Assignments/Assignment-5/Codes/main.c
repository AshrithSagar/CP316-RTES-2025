#include "bsp/bsp.h"
#include "os.h"

#define FPCCR (*(volatile long*)0xE000EF34)

void task1(void) {
    int count = 0;
    while (1) {
        printf("Task 1: %d\n", count++);
        task_yield();
    }
}

int main(void) {
    int count = 0;

    FPCCR &= ~(1 << 30);
    bsp_init();
    task_create(task1);

    while (1) {
        printf("Main: %d\n", count++);
        task_yield();
    }
}
