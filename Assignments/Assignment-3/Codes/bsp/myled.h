#ifndef LED_H
#define LED_H

#define IOREG(addr)   (*((volatile long *) (addr)))

#define GPIO0       0x50000000UL
#define GPIO1       0x50000300UL

#define GPIO_OUT    0x504
#define GPIO_OUTSET 0x508
#define GPIO_OUTCLR 0x50c
#define GPIO_IN     0x510
#define GPIO_DIR    0x514

#define PORT(pin)   (((pin) < 32) ? (GPIO0) : (GPIO1))
#define PIN(pin)    (((pin) < 32) ? (pin) : (pin - 32))

static const unsigned char led_rows[] = {21, 22, 15, 24, 19};
static const unsigned char led_cols[] = {28, 11, 31, 37, 30};

static inline void gpio_set(int pin)
{
    unsigned long baseaddr;

    baseaddr = PORT(pin);
    pin = PIN(pin);

    IOREG(baseaddr + GPIO_DIR) |= (1 << pin);
    IOREG(baseaddr + GPIO_OUTSET) = (1 << pin);
}

static inline void gpio_clear(int pin)
{
    unsigned long baseaddr;

    baseaddr = PORT(pin);
    pin = PIN(pin);

    IOREG(baseaddr + GPIO_DIR) |= (1 << pin);
    IOREG(baseaddr + GPIO_OUTCLR) = (1 << pin);
}

static inline void led_on(int r, int c)
{
    gpio_set(led_rows[r]);
    gpio_clear(led_cols[c]);
}

static inline void led_off(int r, int c)
{
    gpio_clear(led_rows[r]);
    gpio_set(led_cols[c]);
}

static inline void delay(volatile int n)
{
    n *= 1000;
    while (n > 0)
        n--;
}

static inline void led_blink(int r, int c)
{
    while (1)
    {
        led_on(r, c);
        delay(1000);
        led_off(r, c);
        delay(1000);
    }
}

#endif  /* LED_H */
