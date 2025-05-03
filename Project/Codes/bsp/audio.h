#ifndef AUDIO_H
#define AUDIO_H
#include <stdint.h>

/* Audio */
void audio_init(uint32_t speaker_pin, uint32_t mic_pin, uint32_t run_mic_pin);
void audio_beep(int freq, int duration_ms);
void audio_sweep(int fstart, int fend, int duration_ms);
void audio_volume(int volume);
    /* crude volume control based on duty cycle. 50 for normal, 25 for low. */

/* Mic */
void audio_mic_off(void);
void audio_mic_on(void);
#define audio_mic_in    adc_in
#define audio_mic_read  adc_read
    /* After initializing and turning on the mic,
       use ADC routines for reading microphone samples. */

#endif /* AUDIO_H */
