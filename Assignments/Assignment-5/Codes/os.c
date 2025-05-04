#include "os.h"

#define NUM_TASKS 3
#define STACK_SIZE 128

long task_stack[NUM_TASKS][STACK_SIZE];
long task_sp[NUM_TASKS];  // Store SP for each task
int cur_tid = 0;
int task_count = 0;

void task_create(taskfn_t entry) {
    if (task_count >= NUM_TASKS) return;  // Prevent overflow

    long *sp = &task_stack[task_count][STACK_SIZE];
    // Just outside the stack memory

    // Prepare hardware context frame
    *(--sp) = 0x21000000;   // xPSR (default state, interrupts enabled)
    *(--sp) = (long)entry;  // PC (task entry point)
    *(--sp) = 0;            // LR (return address)
    *(--sp) = 0;            // R12
    *(--sp) = 0;            // R3
    *(--sp) = 0;            // R2
    *(--sp) = 0;            // R1
    *(--sp) = 0;            // R0

    // Prepare software context (R4-R11) manually
    for (int i = 4; i <= 11; i++) *(--sp) = 0;

    task_sp[task_count++] = (long)sp;  // Save stack pointer for the task
}

void task_yield(void) { __asm("svc 0"); }
