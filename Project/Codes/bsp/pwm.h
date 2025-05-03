#ifndef PWM_H
#define PWM_H

void pwm_init(int pin);
void pwm_out(int freq, int duty, int duration_ms);

void pwm_on(int freq, int duty);
void pwm_off(void);

#endif  /* PWM_H */
