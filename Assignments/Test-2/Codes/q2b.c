#define TIMEOUT_MS 24 // 24ms => 4m distance (max)
osMutexId_t usonic_mutex;
osSemaphoreId_t usonic_semaphore;
volatile uint32_t echo_start = 0, echo_end = 0;

// Interrupt handler for echo pin change
void ECHO_IRQHandler(void) {
  __disable_irq();
  if (gpio_read(ECHO_PIN)) {
    echo_start = get_time_in_usec();
  } else {
    echo_end = get_time_in_usec();
    osSemaphoreRelease(usonic_semaphore);
  }
  __enable_irq();
}

void usonic_init(void) {
  usonic_mutex = osMutexNew(NULL);
  usonic_semaphore = osSemaphoreNew(1, 0, NULL);
  SetIRQHandler(ECHO_PIN, ECHO_IRQHandler);
}

float usonic_read(void) {
  float distance;

  if (osMutexAcquire(usonic_mutex, osWaitForever) != osOK) {
    return -1.0f; // Mutex acquisition failed
  }

  // Reset timestamps
  echo_start = 0;
  echo_end = 0;

  // Send the trigger pulse
  gpio_write(TRIGGER_PIN, 1);
  delay_us(10);
  gpio_write(TRIGGER_PIN, 0);

  // Wait for echo to start
  if (osSemaphoreAcquire(usonic_semaphore, TIMEOUT_MS) != osOK) {
    osMutexRelease(usonic_mutex);
    return -2.0f; // Timeout (no response)
  }

  // Measure the pulse width
  if (osSemaphoreAcquire(usonic_semaphore, TIMEOUT_MS) != osOK) {
    osMutexRelease(usonic_mutex);
    return -3.0f; // Timeout (out of range)
  }

  uint32_t time_diff;
  __disable_irq();
  time_diff = (echo_end - echo_start);
  __enable_irq();

  osMutexRelease(usonic_mutex);

  // Calculate distance
  distance = (343.0f * time_diff) / (2.0f * 1e6);

  return distance;
}
