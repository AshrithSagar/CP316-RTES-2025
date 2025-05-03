#ifndef BSP_H
#define BSP_H

#include "adc.h"       // IWYU pragma: export
#include "audio.h"     // IWYU pragma: export
#include "gpio.h"      // IWYU pragma: export
#include "ledbtn.h"    // IWYU pragma: export
#include "microbit.h"  // IWYU pragma: export
#include "printf.h"    // IWYU pragma: export
#include "pwm.h"       // IWYU pragma: export
#include "uart.h"      // IWYU pragma: export

void bsp_init(void);

#endif /* BSP_H */
