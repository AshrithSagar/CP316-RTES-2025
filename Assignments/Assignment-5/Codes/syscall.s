    .equ NUM_TASKS, 4

    .syntax unified

    .text
    .thumb_func
    .global SysTick_Handler
    .balign 2

SysTick_Handler:
    // Save software context (R4-R11)
    push {r4-r11}

    // Save current stack pointer
    ldr r0, =cur_tid
    ldr r1, [r0]
    ldr r2, =task_sp
    str sp, [r2, r1, lsl #2]        // Save SP for current task

    // Update to next task
    add r1, r1, #1
    and r1, r1, #(NUM_TASKS - 1)    // Circular scheduling (assumes NUM_TASKS is a power of 2)
    str r1, [r0]                    // Update current task ID

    // Restore next task's stack pointer
    ldr r2, =task_sp
    ldr sp, [r2, r1, lsl #2]

    // Restore software context
    pop {r4-r11}

    bx lr  // Return to task
