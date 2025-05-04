#include "bsp/bsp.h"
#include "os.h"

#define FPCCR (*(volatile long*)0xE000EF34)
#define CVR (*(volatile long*)0xE000E010)
#define CSR (*(volatile long*)0xE000E014)
#define RVR (*(volatile long*)0xE000E018)

void task1(void) {
    int count = 0;
    while (1) {
        printf("Task 1: %d\n", count++);
    }
}

int main(void) {
    int count = 0;

    FPCCR &= ~(1 << 30);
    bsp_init();

    task_create(task1);
    RVR = (64000000 / 1000) * 10;  // 10ms
    CSR = 7;                       // Internal clock; Tick int, Enable

    while (1) {
        printf("Main: %d\n", count++);
    }
}
