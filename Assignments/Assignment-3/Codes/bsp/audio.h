#ifndef AUDIO_H
#define AUDIO_H

/* Audio */
void audio_init(int speaker_pin);
void audio_beep(int freq, int duration_ms);
void audio_sweep(int fstart, int fend, int duration_ms);
void audio_volume(int volume);
    /* crude volume control based on duty cycle. 50 for normal, 25 for low. */

#endif /* AUDIO_H */
