# Exercise 5. Round-robin scheduler

## Files

- `main.c`: Application tasks
- `os.c/.h`:  OS code and header file
- `syscall.s`: System call

## Part 1: Context Switch

Analyze the code and answer the following questions:

1. The code mentiones "hardware context" – what is it?
1. How is `SVC_Handler` called?
1. `SVC_Handler` does not use any of `R4`-`R11`.
Why are they still pushed and popped?
1. Why are there two stacks?
1. What is the purpose of `task_sp` array?
1. Explain `task_create` code.

## Part 2: Round-robin scheduler

Replace `task_yield` with a round-robin scheduler, which schedules mutliple tasks at a specified period.
Test your scheduler with three tasks, where each task does something with the display.

Typically, round-robin scheduling happens very fast (1-10 ms interval) but here, you can schedule each task after a few seconds, so that you can see which task is running by the pattern shown on the display.

Submit a short 30-60 seconds video.
