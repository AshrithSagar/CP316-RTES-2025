#define IOREG(addr) (*((volatile long *)(addr)))

#define GPIO0 0x50000000UL
#define GPIO1 0x50000300UL

#define GPIO_OUT 0x504
#define GPIO_OUTSET 0x508
#define GPIO_OUTCLR 0x50c
#define GPIO_IN 0x510
#define GPIO_DIR 0x514

#define GPIO_CNF(n) (0x700 + 4 * (n))

#define PORT(pin) (((pin) < 32) ? (GPIO0) : (GPIO1))
#define PIN(pin) (((pin) < 32) ? (pin) : (pin - 32))

static const unsigned char led_rows[] = {21, 22, 15, 24, 19};
static const unsigned char led_cols[] = {28, 11, 31, 37, 30};

void gpio_set(int pin) {
    unsigned long baseaddr;

    baseaddr = PORT(pin);
    pin = PIN(pin);

    IOREG(baseaddr + GPIO_DIR) |= (1 << pin);
    IOREG(baseaddr + GPIO_OUTSET) = (1 << pin);
}

void gpio_clear(int pin) {
    unsigned long baseaddr;

    baseaddr = PORT(pin);
    pin = PIN(pin);

    IOREG(baseaddr + GPIO_DIR) |= (1 << pin);
    IOREG(baseaddr + GPIO_OUTCLR) = (1 << pin);
}

void led_on(int r, int c) {
    gpio_set(led_rows[r]);
    gpio_clear(led_cols[c]);
}

void led_off(int r, int c) {
    gpio_clear(led_rows[r]);
    gpio_set(led_cols[c]);
}

void delay(volatile int n) {
    n *= 1000;
    while (n > 0) n--;
}

void led_blink(int r, int c) {
    while (1) {
        led_on(r, c);
        delay(1000);
        led_off(r, c);
        delay(1000);
    }
}

// return 1 if button is pressed, 0 otherwise
// n = button ID, 0 for button A, 1 for button B
int button_get(int n) {
    static int buttons[] = {14, 23};
    unsigned long baseaddr;
    int pin, in;
    int status;

    pin = buttons[n];  // 0 to 41

    baseaddr = PORT(pin);  // PORT0 or PORT1
    pin = PIN(pin);        // 0 to 31 for port 0, 0 to 9 for port 1

    IOREG(baseaddr + GPIO_DIR) &= ~(1 << pin);  // input
    IOREG(baseaddr + GPIO_CNF(pin)) = 0;        // direction input, connected

    in = IOREG(baseaddr + GPIO_IN);  // signal levels for pins 0 to 31

    // refer to schematics for signal details
    if (in & (1 << pin))  // pin high, button released
        status = 0;
    else  // pin low, button pressed
        status = 1;

    return status;
}
