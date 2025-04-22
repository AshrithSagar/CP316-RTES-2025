# CP316: Real-time Embedded Systems: Final Exam

Date: 23-30 April 2025

This is a take-home exam.
It should take about 3 hours.
Spending about an hour in part (A), understanding the functionality, dividing it into various tasks and ISRs and thinking through the key issues will help.

Subsequently, spend 20-30 minutes on each of B, C and D.
Finally, complete your answers with E.
Don’t worry about getting everything perfect.
Ensure that the key aspects of the design are covered and presented properly.

You may make reasonable assumptions and state them clearly.
Feel free to reach out for clarifications or discussions.

## System Scenario

You are designing embedded software for a small autonomous robot with line-following, obstacle avoidance, audio interaction and debugging capabilities.
The system runs on a microcontroller with an RTOS.

## Hardware and Interfaces

- Eight binary light sensors for line following (high for light, low for dark)
- Ultrasonic distance sensor (front-facing)
- Two motors (left and right)
- Microphone connected via ADC
- Radio link (for debug messages from tasks)

## System Behavior

1. On power-up, the system waits in idle mode.

2. On a valid voice command, the robot starts moving and follows the line using the light sensors.
   You don't need to implement the control algorithm for line-following; assume a black-box function is available that takes sensor input and returns motor duty cycles.

3. If an obstacle is detected within 30 cm, the robot stops and waits until the obstacle is cleared before resuming line-following.

4. The robot listens for voice commands through the microphone.
   A start word (such as "go") starts the robot, and a stop word (such as "stop") halts its operation and returns it to idle mode.

5. The microphone is connected to a 16-bit ADC that triggers an interrupt at 8 kHz sampling rate.

6. All tasks use the radio link for debugging.
   Debug messages can be printed into a buffer (`sprintf`) and then the buffer can be transmitted over the radio interface.

## Voice Command Detection Details

The algorithm checks for known words using a lightweight pattern-matching technique.

- The detection algorithm is implemented as a black-box function that takes in a window (buffer) of audio samples, updates its internal state, and returns a decision: index of the word detected, or -1 for detection in progress.

- The algorithm runs window by window, where each window is of 32 ms duration.
  Once a window is passed to the algorithm, its samples are no longer required and can be discarded or reused.

- The algorithm takes about 8ms to 12ms to execute.

- The algorithm requires a minimum of 4 consecutive windows to make a decision.

## Answer the following

Design the system as a collection of ISRs, timer callbacks and tasks.
You also need to include mutual exclusion, synchronization and memory management objects as required.

You may assume availability of the following RTOS objects: tasks (with priorities), semaphores (binary and counting), mutexes, message queues, memory pools and timers.

`C`-like pseudocode is acceptable; the exact syntax is not important.

(A). Draw the block diagram of the system that includes the functional blocks (ISRs, timer callbacks and tasks).

Define the priorities of tasks.

Periodicity of the timer callbacks.

Indicate which ISR or task is interfaced with which hardware.
Draw the data flows:

- Between the hardware and the functional block
- Between two functional blocks

(B). Describe synchronization mechanisms for the following:

- Receiving audio samples
- Receiving echo pulse for the ultrasonic sensor
- Sending debug messages over the radio link.

(C). Define the memory management scheme for the audio buffers, using statically or dynamically allocated buffers.

(D). Identify any shared resources and specify if they need protection.

(E). Finally, provide a `C`-like pseudo-code for all the functional blocks.

You may use `analogRead()` for the microphone and `digitalRead()` for the light sensors and ultrasonic echo pulse.

You may use `radioSend()` to send a buffer of data over the radio link.

If you need any other functionality, assume a suitable API and state it clearly.
