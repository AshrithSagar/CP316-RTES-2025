#include "audio.h"
#include "pwm.h"

/* Initialize speaker */
void audio_init(int speaker_pin)
{
    /* Speaker is connected to a PWM pin. We can use it to play tones by
     * generating a square wave at a specific frequency.
     */
    pwm_init(speaker_pin);

    /* Set volume */
    audio_volume(30);      // 50 normal, 25 low
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
