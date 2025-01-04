#ifndef UART_H
#define UART_H

#include <stdint.h>

extern void uart_init(uint32_t rxpin, uint32_t txpin);
extern void uart_putc(char ch);
extern void uart_puts(char s[]);

#endif /* UART_H */
