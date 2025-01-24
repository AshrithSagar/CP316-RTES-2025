# ex3-poll

Implement game of catch by polling the buttons.

1. Catch starts at the center of the bottom row.
1. Catch moves by left or right by one position according to the button-press.
1. Ball begins dropping from a random position.
1. If it is caught successfully, the speed increases in the next round.
(You may saturate the speed at a certain level.)

## Files

Names are self-explanatory.

- `startup.c`
- `system.c`
- `main.c`
- `nrf52833.ld`
- `build.sh`
- `clean.sh`
- `Makefile`
- `bsp/`
  - `bsp.c`, `bsp.h`
  - `gpio.c`, `gpio.h`
  - `ledbtn.c`, `ledbtn.h`
  - `uart.c`, `uart.h`
  - `printf.c`, `print.h`
  - `pwm.c`, `pwm.h`
  - `audio.c`, `audio.h`
  - `timer.c`, `timer.h`
  - `build_lib.sh`
  - `Makefile`

## Questions

1. Explain the objective and functionality of `led_row_refresh` function.

    a. How frequently it is called? Why?

    b. Who calls it?

    c. What happens if the processor is stuck into a delay loop when the display need to be refreshed?

1. How is a frequency sweep generated?

1. What is the worst-case response time for the button-press inputs in your program?
What does it depend on?

**Try this out (just for fun, no points)**

Keyboard keys are typically polled periodically at a configurable key repetation rate (KRR).

Create a software timer that polls the buttons periodically and moves the catch accordingly.
The KRR can be determined based on your reaction time.
