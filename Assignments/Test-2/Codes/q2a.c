#define TIMEOUT_US 24000 // 24000us => 4m distance (max)
osMutexId_t usonic_mutex;

void usonic_init(void) { usonic_mutex = osMutexNew(NULL); }

float usonic_read(void) {
  float distance;

  if (osMutexAcquire(usonic_mutex, osWaitForever) != osOK) {
    return -1.0f; // Mutex acquisition failed
  }

  // Send the trigger pulse
  gpio_write(TRIGGER_PIN, 1);
  delay_us(10);
  gpio_write(TRIGGER_PIN, 0);

  // Wait for echo to start
  unsigned long wait_start = get_time_in_usec();
  while (gpio_read(ECHO_PIN) == 0) {
    if ((get_time_in_usec() - wait_start) > TIMEOUT_US) {
      osMutexRelease(usonic_mutex);
      return -2.0f; // Timeout (no response)
    }
  }

  // Measure the pulse width
  unsigned long start_time = get_time_in_usec();
  while (gpio_read(ECHO_PIN) == 1) {
    if ((get_time_in_usec() - start_time) > TIMEOUT_US) {
      osMutexRelease(usonic_mutex);
      return -3.0f; // Timeout (out of range)
    }
  }

  unsigned long end_time = get_time_in_usec();
  osMutexRelease(usonic_mutex);

  // Calculate distance
  distance = (343.0f * (end_time - start_time)) / (2.0f * 1e6);

  return distance;
}
