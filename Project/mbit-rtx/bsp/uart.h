#ifndef UART_H
#define UART_H

#include <stdint.h>

extern void uart_init(uint32_t rxpin, uint32_t txpin);
extern char uart_getc_nowait(void);
extern char uart_getc(void);
extern int  uart_gets(char s[]);
extern void uart_putc_nowait(char ch);
extern void uart_putc(char ch);
extern void uart_puts(char s[]);
extern void uart_putd(char *name, int v);
extern void uart_putx(char *name, int v);

typedef void (* uart_callback_t)(char ch);
extern void uart_inten(uint32_t event, uart_callback_t uart_callback);
#define UART_INTEN_RXDRDY (1 << 2)
#define UART_INTEN_TXDRDY (1 << 7)

#endif /* UART_H */
