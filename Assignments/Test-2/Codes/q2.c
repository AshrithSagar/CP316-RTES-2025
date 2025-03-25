float usonic_read(void) {
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
