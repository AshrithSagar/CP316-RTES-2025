#ifndef UART_H
#define UART_H

extern void uart_init(int rxpin, int txpin);
extern void uart_putc(char ch);
extern void uart_puts(char s[]);

#endif /* UART_H */
