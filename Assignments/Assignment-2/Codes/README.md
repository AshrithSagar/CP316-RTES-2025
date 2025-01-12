# Exercise 2: Timers

In this exercise, we will experiment with the SysTick timer.

## Files

- `startup.c`: Vector table, default ISRs, startup code
- `system.c`: System initialization: initializes FPU and clock
- `main.c`:  Empty application main
- `ledbtn.h/.c`: Simple LED and button code
- `timer.h/.c`: Software timer header file and code
- `uart.h/.c`: UART header file and code
- `printf.h/.c`: Simplified printf to print basic formats
- `microbit.h`: Pin details of microbit board
- `bare.ld`:  Linker command file containing memory configuration of the processor
- `build.sh`, `clean.sh`: Scripts to build the code and cleanup binary files

Please note that printf is rudimentary: it only supports `"%c"`, `"%s"`, `"%d"`, `"%x"` and `"%f"`, with `"%f"` up to two decimal points.
It does not support formats like `"%3.2f"`.

## Part 1: Timing measurements

Program SysTick with a maximum reload value of `0x00FFFFFF` and use CVR for timing measurements.

Measure the following:

1. Function-call and loop overheads, and clock cycles per iteration in `delay()` function.
1. Time spent to transmit one character.
1. Average human reaction-time to click (press and release) a button.

You may experiment with different loop sizes, multiple characters and mutliple switch presses to arrive at a "reasonably" accurate result.

## Part 2: Stopwatch

Implement a stopwatch to measure the time between two button-presses.
The resolution should be one-tenth of a second.

- Start on the first click (press and release)
- Print value every one-tenth of a second on the terminal.
- Stop on the second click (press and release).
- Print the final value.

You may try printing only with the carriage return (CR) without the linefeed (LF) character to keep displaying on the same line.

It may help to read about key debouncing.
If you experience bouncing in your experiments, please describe how you solved it.

## Part 3: Display refresh

Implement display refresh using software timer, which should display contents of the frame buffer on the matrix display, one LED at a time.
In each timer callback, turn on the current LED if it is set in the frame buffer, and keep it on until the next callback.
At the next callback, turn off the previous LED and move to the next LED.

In the code, explain what the duration should be to see a persistent display.

Integrate part 2 and 3.
You should see the matrix display while running the stopwatch.

## Submission

Part 1: `main.c` files for each experiment and a document with the results.

Part 2 and 3: combined `main.c` file along with a short video showing display and stopwatch running.
