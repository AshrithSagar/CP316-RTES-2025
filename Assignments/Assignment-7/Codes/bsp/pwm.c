#include <stdint.h>
#include <string.h>
#include "pwm.h"

/*
 * We will use PWM to provide a square wave to the speaker.
 * We can play various tones by setting the frequency of PWM.
 */

#ifndef IOREG32
#define IOREG32(addr) (*(volatile unsigned long *) (addr))
#endif

/*
 * NRF52 has a PWM that has more functionality than what we need.
 * Hence, we are using a subset of the PWM registers here.
 */

/* Register offsets */
#define PWM_STOP       		IOREG32(0x4001C004)     // stop pwm
#define PWM_SEQ0START  		IOREG32(0x4001C008)     // start sequence 0
#define PWM_EVENTS_STOPPED  IOREG32(0x4001C104)     // event to indicate PWM stopped
#define PWM_EVENTS_SEQ0END  IOREG32(0x4001C110)     // event to indicate sequnce 0 ended
#define PWM_ENABLE          IOREG32(0x4001C500)     // enable / disable pwm
#define PWM_COUNTERTOP      IOREG32(0x4001C508)     // to decide PWM frequncy
                                                    //   countertop = pwm clock / pwm freq
#define PWM_PRESCALER       IOREG32(0x4001C50C)     // divisor for PWM clock (2 power n)
#define   PRESCALER_DIV32   5                       //  divide by 32
#define PWM_SEQ0PTR         IOREG32(0x4001C520)     // address where the sequence is stored
#define PWM_SEQ0CNT         IOREG32(0x4001C524)     // number of values in the sequence
#define PWM_SEQ0REFRESH     IOREG32(0x4001C528)     // additional pwm cycles between two
                                                    //   values of the sequence
#define PWM_SEQ0ENDDELAY    IOREG32(0x4001C52C)     // additional pwm cycles at the end

#define PWM_PSEL            IOREG32(0x4001C560)     // pin select

static uint16_t s_sequence[2];

/* PWM clock:
 *  PWM frequency = PWM clock / PWM counter
 *  Hence, lowest frequency = pwm clock / max count
 *
 *  Procssor uses a 15-bit counter with max value of 32767.
 *  For PWM clock of 1 MHz, lowest frequency = 1000000/32767 = ~30 Hz
 *  For PWM clock of 0.5 MHz, lowest frequency = 500000/32767 = ~15 Hz
 * Here, we selct 0.5 MHz clock for audio frequencies starting from 20 Hz.
 */
#define PWM_CLK 500000

/* APIs */

void pwm_init(int pin)
{
    /* PWM clock is 16 MHz. Hence, Prescaler divisor = 32 for 500 kHz clock */
    PWM_PRESCALER = PRESCALER_DIV32;

    /* Connect the port to the pin */
    PWM_PSEL = pin;

    /* Enable PWM */
    PWM_ENABLE = 1;
}

/* Generate a PWM wave of the specified duty cycle for the specified duration
 *  duty cycle in integer percentage, for example, 50.
 */
void pwm_out(int freq, int duty, int duration_ms)
{
    int n_pwm_cycles = (freq * duration_ms) / 1000;
    uint16_t countertop;

    /* Set PWM counter for the required frequency. */
    countertop =  PWM_CLK / freq;
    PWM_COUNTERTOP = countertop;

    /* To generate n PWM cycles, we create a sequence of two identical values
     * with (n-2) cycles gap in-between.
     */
    PWM_SEQ0PTR = (uint32_t) s_sequence;
    PWM_SEQ0CNT = 2;
    PWM_SEQ0REFRESH = n_pwm_cycles - 2;

    /* Set count values for specified duty cycle */
    s_sequence[0] = (countertop * duty) / 100;
    s_sequence[1] = (countertop * duty) / 100;

    /* Start sequence 0 */
    PWM_SEQ0START = 1;

    /* Wait for the sequence to complete */
    while (PWM_EVENTS_SEQ0END == 0)
        ;
    PWM_EVENTS_SEQ0END = 0;

    /* Stop PWM */
    PWM_STOP = 1;
    while (PWM_EVENTS_STOPPED == 0)
        ;
    PWM_EVENTS_STOPPED = 0;
}

void pwm_on(int freq, int duty)     // duty in %age
{
    static uint16_t s_sequence;
    uint32_t countertop;

    countertop = PWM_CLK / freq;                // period in clock cycles
    PWM_COUNTERTOP = countertop;

    s_sequence = (countertop * duty) / 100;     // duty cycle counts
    PWM_SEQ0PTR = (uint32_t) &s_sequence;
    PWM_SEQ0CNT = 1;            // one duty cycle value
    PWM_SEQ0REFRESH = 0;        // continuous

    /* Start sequence 0 */
    PWM_SEQ0START = 1;
}

void pwm_off(void)
{
    /* Stop PWM */
    PWM_STOP = 1;
    while (PWM_EVENTS_STOPPED == 0)
        ;
    PWM_EVENTS_STOPPED = 0;
}
