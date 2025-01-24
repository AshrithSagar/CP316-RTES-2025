#include <stdint.h>
#include "gpio.h"
#include "uart.h"

#ifndef IOREG32
#define IOREG32(addr) (*(volatile unsigned long *) (addr))
#endif

/*
 * UART Registers:
 * 1. Tasks, also called command registers to start, stop and enable/disable
 * 2. Events
 * 3. Pin select (which pins connect to rx/tx)
 * 4. Data
 * 5. Configuration (baud rate, parity)
 */

/* 1. Task registers */
#define UART_STARTRX   		IOREG32(0x40002000)        // start rx
#define UART_STARTTX   		IOREG32(0x40002008)        // start tx
#define UART_ENABLE    		IOREG32(0x40002500)        // enable/disable
#define   UART_ENABLE_Disabled  0
#define   UART_ENABLE_Enabled   4

/* 2. Event registers */
#define UART_RXDRDY    		IOREG32(0x40002108)        // rx ready flag
#define UART_TXDRDY    		IOREG32(0x4000211c)        // tx ready flag
#define UART_INTENSET  		IOREG32(0x40002304)        // int enable

/* 3. Tx and Rx pin select registers:
 * pin numbers are defined as port*32 + pin
 * for example, P0_6 = 6, P1_6 = 38
 */
#define UART_PSELTXD   		IOREG32(0x4000250c)        // tx pin number
#define UART_PSELRXD   		IOREG32(0x40002514)        // rx pin number

/* 4. Data registers */
#define UART_RXD       		IOREG32(0x40002518)
#define UART_TXD       		IOREG32(0x4000251c)

/* 5. Configurtion */

/* Baud rate register and values */
#define UART_BAUDRATE  		IOREG32(0x40002524)
#define   UART_BAUDRATE_115200 0x01d60000
                                // There are many other baud rate defines
                                // ranging from 9600 to 1M. We're using only
                                // the one that we need.

/* Flow control and parity */
#define UART_CONFIG    		IOREG32(0x4000256c)
#define   UART_CONFIG_HWFC_Off  0
#define   UART_CONFIG_HWFC_On   1
#define   UART_PARITY_None      0
#define   UART_PARITY_Even      (7 << 1)


/* NVIC registers */
#define NVIC_ISER           IOREG32(0xE000E100)
#define UART0_ID            2               // peripheral ID

void uart_init(uint32_t rxpin, uint32_t txpin)
{
    /* Disable while changing parameters */
    UART_ENABLE = UART_ENABLE_Disabled;

    /* Set up pins to maintain signal levels while UART disabled */
    gpio_out(txpin, DRIVE_STANDARD);            // output
    gpio_in(rxpin, PULL_NONE);  // input
    gpio_set(txpin);            // set tx high

    /* Connect UART to port pins */
    UART_PSELTXD = txpin;
    UART_PSELRXD = rxpin;

    /* UART parameters */
    UART_BAUDRATE = UART_BAUDRATE_115200;
    UART_CONFIG = UART_CONFIG_HWFC_Off | UART_PARITY_None;

    /* Configuration complete. Now enable the UART. */
    UART_ENABLE = UART_ENABLE_Enabled;

    /* Start Rx and Tx */
    UART_STARTTX = 1;
    UART_STARTRX = 1;

    /* Clear Rx ready flag */
    UART_RXDRDY = 0;
}

char uart_getc_nowait(void)
{
    return UART_RXD;
}

char uart_getc(void)
{
    char ch;

    /* Wait for a character to arrive on TTY */
    while (UART_RXDRDY == 0)    // wait for the flag
        ;

    /* Data received. Read it and clear the flag. */
    ch = UART_RXD;
    UART_RXDRDY = 0;

    return ch;
}

int uart_gets(char *s)
{
    char ch;
    char *p = s;
    int len = 0;

    while(1)
    {
        ch = uart_getc();

        if ((ch == '\n') || (ch == '\r'))
            break;

        *p++ = ch;

        len++;
    }
    
    *p = '\0';  // null-terminate the string

    return len;
}

void uart_putc_nowait(char ch)
{
    UART_TXD = ch;
}

void uart_putc(char ch)
{
    /* Write into data buffer and wait till tx complete */
    UART_TXD = ch;
    while (UART_TXDRDY == 0)
        ;

    /* Clear the event */
    UART_TXDRDY = 0;

    return;
}

void uart_puts(char s[])
{
    char *p;

    for (p = s; *p; p++)
        uart_putc(*p);
}

static uart_callback_t uart_rx_callback = 0, uart_tx_callback = 0;

void uart_inten(uint32_t event, uart_callback_t callback)
{
    if (event & UART_INTEN_RXDRDY)
    {
        if (callback)   // non-zero
            UART_INTENSET |= UART_INTEN_RXDRDY;     // set
        else
            UART_INTENSET &= ~UART_INTEN_RXDRDY;    // clear
        uart_rx_callback = callback;
    }
    if (event & UART_INTEN_TXDRDY)
    {
        if (callback)   // non-zero
            UART_INTENSET |= UART_INTEN_TXDRDY;     // set
        else
            UART_INTENSET &= ~UART_INTEN_TXDRDY;    // clear

        uart_tx_callback = callback;
    }

    /* Enable GPIOTE interrupts in the interrupt controller */
    NVIC_ISER |= (1 << UART0_ID);
}

void UARTE0_UART0_IRQHandler(void)
{
    if (UART_RXDRDY != 0)
    {
        if (uart_rx_callback != 0)
            uart_rx_callback(UART_RXD);
        UART_RXDRDY = 0;
    }
    if (UART_TXDRDY != 0)
    {
        if (uart_tx_callback != 0)
            uart_tx_callback(UART_TXD);
        UART_TXDRDY = 0;
    }
}
