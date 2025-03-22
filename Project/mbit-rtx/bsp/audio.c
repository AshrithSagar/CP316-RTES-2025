#include <stdint.h>
#include <math.h>
#include <ctype.h>
#include "audio.h"
#include "gpio.h"
#include "pwm.h"
#include "adc.h"

static uint32_t s_run_mic;
/* Initialize speaker and mic */
void audio_init(uint32_t speaker_pin, uint32_t mic_pin, uint32_t run_mic_pin)
{
    /* Speaker is connected to a PWM pin. We can use it to play tones by
     * generating a square wave at a specific frequency.
     */
    pwm_init(speaker_pin);

    /* Set volume */
    audio_volume(30);      // 50 normal, 25 low

    /* Initialize ADC for receiving microphone samples. */
    adc_init(mic_pin);

    /* Local copy of run_mic pin for later turning the mic on/off */
    s_run_mic = run_mic_pin;
}

void audio_mic_off(void)
{
    /* Switch off supply to mic circuit */
    gpio_out(s_run_mic, DRIVE_STANDARD);    // no need for high drive current
    gpio_clear(s_run_mic);                  // turn off the supply
}

void audio_mic_on(void)
{
    /* Turn on the microphone circuit */
    gpio_out(s_run_mic, DRIVE_HIGH);    // supplies voltage to circuit, hence
                                        // configured for high drive current
    gpio_set(s_run_mic);                // turn on the mic
}

/* Duty cycle can be used to control volume. It is not linear but we can
   turn the volume low during debugging. */
static int duty_cycle;

void audio_volume(int volume)
{
    duty_cycle = volume;
}

/* Play a beep at the specified frequency for the specified duration. */
void audio_beep(int freq, int duration_ms)
{
    /* Generate pwm with the specified frequency */
    pwm_out(freq, duty_cycle, duration_ms);
}

/* Play all the frequencies from start to end for a given duration. */
void audio_sweep(int fstart, int fend, int duration_ms)
{
    int step_duration = 20;     // in milliseconds
    int steps = duration_ms / step_duration;
    int fdelta = (fend - fstart) / steps;
    int f;

    /* Play the sweep as small steps of increasing / decreasing frequencies. */
    f = fstart;
    while (steps > 0)
    {
        audio_beep(f, step_duration);

        f += fdelta;
        steps--;
    }
}
