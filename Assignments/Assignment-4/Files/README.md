# Ex4-interrupts

Implement game of catch using button interrupts.
The rules remain the same:

1. Catch is placed at the center of the bottom row.
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

Read Section 9 GPIOTE in nRF52833_v1.5 product specifications, available under Files/Datasheets.
Also refer to the switch interfacing circuit in the schematics.

Explain the sequence from the button-press till interrupt handler returns and main code resumes.
