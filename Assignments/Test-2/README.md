# Test-2

Date: 25 March 2025

1. Max marks: 10
1. This is open-everything test.
However, it is important that your answers reflect how well you have understood the concepts.
Hence, please write the answers in your own words in simple terms, instead of using Al's responses directly.
1. This is an individual test, no collaboration permitted.
1. Make and state assumptions as required.

## Question 1

While debugging my code, I found that variable `x` was getting overwritten somewhere.
I did not know where, so I wrote the following function to write its value in a buffer, along with a timestamp.

```C
#define BUFSIZ 1024

int count = 0;
int buf[BUFSIZ];

void dumpx()
{
  extern int x;

  buf[count] = get_time_in_usec();
  count = (count + 1) % BUFSIZ;

  buf[count] = x;
  count = (count + 1) % BUFSIZ;
}
```

The function `get_time_in_usec` returns the value of a 32-bit timer, which counts the number of 1 us ticks since the timer was initialized.

It worked fine in my standalone code.
But once I start using it in a multitasking system from different tasks and ISRs, the logged values were often inconsistent.

- Can you explain why?
- And what should be done to fix?

## Question 2 $\mid$ Ultrasonic sensor

A system uses an ultrasonic sensor to measure the distance from a surface in the front.

The sensor has two pins: trigger and echo.
Both are connected to GPIO pins on a microcontroller.

- Trigger is an output pin.
    We need to set it high for 10 ms to start the measurement.
    The sensor sends out a sound wave in the form of a series of pulses of ultrasonic frequency.
    The wave echoes back after hitting a surface.
    The time of echo is used to measure the distance from the surface.
- Echo is an input pin.
    It remains high for the duration of echo.
    For example, if it takes 10 ms for the sound wave to hit a surface and return, the echo pin remains high for 10 ms.

Distance can be calculated by the formula: `d = v * T / 2` \
where, `v` = velocity of sound = 343 m/s` \
`T` = time taken for wave to hit the surface and return (traveling total distance 2d).

The pulse width is clipped at 24 ms corresponding to approximately 4 m distance.
Distances larger than 4 m are considered out of range.
Now, consider the implementation of an ultrasonic sensor read function:

```C
float usonic_read(void)
{
  float distance;

  // Send the trigger pulse
  gpio_write(TRIGGER_PIN, 1);
  delay_us(10);
  gpio_write(TRIGGER_PIN, 0);

  // Wait for echo to start
  while (gpio_read(ECHO_PIN) == 0)
    ;

  // Measure the pulse width
  unsigned long start_time = get_time_in_usec();
  while (gpio_read(ECHO_PIN) == 1)
    ;

  unsigned long end_time = get_time_in_usec();

  // Calculate distance
  distance = (343.0f * (end_time - start_time)) / 2.0f;

  return distance;
}
```

Answer the following:

- What real-time issues do you see in the function above?
- How should the function be modified so that it can be used from multiple threads?

---
