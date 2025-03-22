#include <stdint.h>
#include <stdio.h>      // snprintf
#include <math.h>       // pi, sin, cos
#include "encoder.h"
#include "gpio.h"

// Constants
#define WHEEL_DIAMETER 0.1f // Wheel diameter in m
#define WHEEL_BASE 0.215f   // Distance between wheels in m
#define PRR 140.0f          // Pulses per revolution
                            // old bot 140, new bot 325

// Encoder Counters
volatile int32_t left_encoder_count = 0;
volatile int32_t right_encoder_count = 0;

// Previous Encoder Counts
int32_t left_encoder_prev = 0;
int32_t right_encoder_prev = 0;

// Current Position and Orientation
float x_pos = 0.0;
float y_pos = 0.0;
float theta = 0.0;

// Movement Direction (Set via commands)
int left_motor_direction = 1;   // 1 for forward, -1 for reverse
int right_motor_direction = 1;  // 1 for forward, -1 for reverse

// GPIO Callback Functions for Encoders
void left_encoder_callback() {
    left_encoder_count += left_motor_direction;
}

void right_encoder_callback() {
    right_encoder_count += right_motor_direction;
}

void encoder_init(int pin1, int pin2)
{
    gpio_in(pin1, PULLDOWN);
    gpio_inten(pin1, 0, GPIO_RISINGEDGE, right_encoder_callback);

    gpio_in(pin2, PULLDOWN);
    gpio_inten(pin2, 1, GPIO_RISINGEDGE, left_encoder_callback);
}

float calculate_distance(int32_t delta_counts) {
    return (delta_counts / (float) PRR) * (M_PI * WHEEL_DIAMETER);
}

void update_odometry() {
    // Calculate encoder deltas
    int32_t left_delta = left_encoder_count - left_encoder_prev;
    int32_t right_delta = right_encoder_count - right_encoder_prev;

    // Update previous counts
    left_encoder_prev = left_encoder_count;
    right_encoder_prev = right_encoder_count;

    // Calculate distances
    float left_distance = calculate_distance(left_delta);
    float right_distance = calculate_distance(right_delta);

    // Calculate linear displacement and heading change
    float delta_d = (left_distance + right_distance) / 2.0;
    float delta_theta = (right_distance - left_distance) / WHEEL_BASE;

    // Update pose
    theta += delta_theta;
    theta = fmod(theta, 2.0 * M_PI);
    x_pos += delta_d * cos(theta);
    y_pos += delta_d * sin(theta);
}

void get_odometry(char s[]) {
    // unsafe, potential string overflow
    sprintf(s, "P,%f,%f,%f\n", x_pos, y_pos, theta);
}
