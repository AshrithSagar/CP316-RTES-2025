#ifndef MICROBIT_H
#define MICROBIT_H

/* Pin definitions for microbit v2 */

/* LEDs definitions for 5x5 matrix display */
#define LED_NUM_ROWS 5
#define LED_NUM_COLS 5

#define LED_ROW0 21
#define LED_ROW1 22
#define LED_ROW2 15
#define LED_ROW3 24
#define LED_ROW4 19

#define LED_COL0 28
#define LED_COL1 11
#define LED_COL2 31
#define LED_COL3 37
#define LED_COL4 30

/* Buttons */
#define BUTTONS_NUMBER 2

#define BUTTON_0 14
#define BUTTON_1 23

#define BUTTONS_ACTIVE_STATE 0

/* UART */
#define UART_RX 40 // P1_08
#define UART_TX 6  // P0_06

/* I2C */
#define I2C_SCL 8  // P0_08
#define I2C_SDA 16 // P0_16

/* On-board speaker and mic */
#define SPEAKER 0 // P0_00
#define MIC 3     // AIN3 on P0_05
//  (we need to specify analog input channel,
//   and not the pin number)
#define RUN_MIC 20 // P0_20

/* Edge connector pins */
#define P0 2
#define P1 3
#define P2 4
#define P8 10
#define P12 12
#define P16 34

#endif /* MICROBIT_H */
