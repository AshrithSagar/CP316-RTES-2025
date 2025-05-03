#ifndef ENCODER_H
#define ENCODER_H

void encoder_init(int pin1, int pin2);
void update_odometry(void);
void get_odometry(char s[]);

#endif /* ENCODER_H */
