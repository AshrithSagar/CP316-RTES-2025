# ex6. rtx

Port RTX as discussed in the class.

Submit a video along with half to one page write up of what you learnt in the process.

---

## Directory Structure

> Commit used from [`ARM-software/CMSIS_5`](https://github.com/ARM-software/CMSIS_5) repo: [`2b7495b8535bdcb306dac29b9ded4cfb679d7e5c`](<https://github.com/ARM-software/CMSIS_5/tree/2b7495b8535bdcb306dac29b9ded4cfb679d7e5c>)

```plaintext
mbit-rtx
|--  Makefile
|--  bsp
|   |--  Makefile
|   |--  adc.c
|   |--  adc.h
|   |--  audio.c
|   |--  audio.h
|   |--  bsp.c
|   |--  bsp.h
|   |--  build_lib.sh
|   |--  clean.sh
|   |--  gpio.c
|   |--  gpio.h
|   |--  ledbtn.c
|   |--  ledbtn.h
|   |--  microbit.h
|   |--  myled.h
|   |--  nrf52833.h
|   |--  printf.c
|   |--  printf.h
|   |--  pwm.c
|   |--  pwm.h
|   |--  timer.c
|   |--  timer.h
|   |--  uart.c
|   |--  uart.h
|--  build.sh
|--  clean.sh
|--  main.c
|--  nrf52833.ld
|--  rtx
|   |--  RTX_Config.c
|   |--  RTX_Config.h
|   |--  arch
|   |   |--  ARMCM4.h
|   |   |--  ARMCM4_FP.h
|   |   |--  cmsis_compiler.h
|   |   |--  cmsis_gcc.h
|   |   |--  cmsis_version.h
|   |   |--  core_cm4.h
|   |   |--  mpu_armv7.h
|   |   |--  system_ARMCM4.h
|   |--  cmsis_os2.h
|   |--  irq_armv7m.S
|   |--  os_systick.c
|   |--  os_tick.h
|   |--  rtx_core_c.h
|   |--  rtx_core_ca.h
|   |--  rtx_core_cm.h
|   |--  rtx_def.h
|   |--  rtx_delay.c
|   |--  rtx_evflags.c
|   |--  rtx_evr.c
|   |--  rtx_evr.h
|   |--  rtx_kernel.c
|   |--  rtx_lib.c
|   |--  rtx_lib.h
|   |--  rtx_memory.c
|   |--  rtx_mempool.c
|   |--  rtx_msgqueue.c
|   |--  rtx_mutex.c
|   |--  rtx_os.h
|   |--  rtx_semaphore.c
|   |--  rtx_system.c
|   |--  rtx_thread.c
|   |--  rtx_timer.c
|--  rules.mk
|--  startup.c
|--  system.c
```

---
