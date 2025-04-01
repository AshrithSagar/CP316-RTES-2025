#ifndef PRINTF_H
#define PRINTF_H

/* define putchar as the function that transmits a character */
#define putchar uart_putc

void putchar(char c);
int puts(const char s[]);
int printf(const char *fmt, ...);

#endif /* PRINTF_H */
