#include "os.h"

#define STACK_SIZE 128
#define NUM_TASKS 3

long task_sp[NUM_TASKS];  // Stack pointers for tasks
long task_stack[NUM_TASKS][STACK_SIZE];
int cur_tid = 0;

void task_create(taskfn_t entry) {
    long *sp = &task_stack[cur_tid][STACK_SIZE];
    // Top of the stack for the task
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

    task_sp[cur_tid] = (long)sp;  // Save stack pointer for the task
    cur_tid++;
}
