// --- ISR: ADC sampling ---
void ADC_IRQHandler(void) {
  static uint16_t idx = 0;
  audioBuf[prodIdx][idx++] = analogRead();
  if (idx >= AUDIO_WINDOW_SAMPLES) {
    idx = 0;
    // swap buffers
    disableADCInterrupt();
    prodIdx ^= 1;
    consIdx ^= 1;
    enableADCInterrupt();
    xSemaphoreGiveFromISR(audioSem, NULL);
  }
}

// --- Timer callback: ultrasonic trigger ---
void TimerCallback(void) {
  digitalWrite(ULTRASONIC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG, LOW);
}

// --- ISR: ultrasonic echo ---
void Echo_IRQHandler(void) {
  static uint32_t start;
  if (digitalRead(ECHO_PIN))
    start = micros();
  else {
    uint32_t duration = micros() - start;
    distanceCm = duration / 58;
    xSemaphoreGiveFromISR(echoSem, NULL);
  }
}

// --- AudioProc Task ---
void AudioTask(void \*pv) {
  int16_t buffer[AUDIO_WINDOW_SAMPLES];
  for (;;) {
    xSemaphoreTake(audioSem, portMAX_DELAY);
    memcpy(buffer, audioBuf[consIdx], sizeof(buffer));
    int word = detectWord(buffer);
    if (word >= 0)
      xQueueSend(cmdQueue, &word, 0);
  }
}

// --- Control Task ---
void ControlTask(void \*pv) {
  enum { IDLE, FOLLOW, STOPPED } state = IDLE;
  for (;;) {
    int cmd;
    if (xQueueReceive(cmdQueue, &cmd, 0) == pdPASS) {
      if (cmd == START && state == IDLE)
        state = FOLLOW;
      else if (cmd == STOP)
        state = IDLE;
    }
    if (state == FOLLOW) {
      if (xSemaphoreTake(echoSem, 0) == pdPASS) {
        if (distanceCm < 30)
          state = STOPPED;
      }
      if (state == FOLLOW) {
        int motors[2];
        blackBoxLineFollow(digitalReadSensors(), motors);
        setMotorDuty(motors[0], motors[1]);
      }
    } else if (state == STOPPED) {
      setMotorDuty(0, 0);
      if (xSemaphoreTake(echoSem, portMAX_DELAY) == pdPASS && distanceCm >= 30)
        state = FOLLOW;
    } else { // IDLE
      setMotorDuty(0, 0);
    }
    // send debug
    char msg[64];
    sprintf(msg, "State=%d Dist=%d\n", state, distanceCm);
    xQueueSend(debugQueue, msg, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

// --- RadioTx Task ---
void DebugTask(void \*pv) {
  char msg[64];
  for (;;) {
    if (xQueueReceive(debugQueue, msg, portMAX_DELAY) == pdPASS)
      radioSend(msg, strlen(msg));
  }
}
