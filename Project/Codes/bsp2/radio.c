#include <string.h>
#include "radio.h"

#define GROUP 17
#define FREQ  7                 /* Frequency 2407 MHz */
#define RADIO_PACKET 128

#define RADIO_BASE0             (* (volatile unsigned long *) 0x4000151c)
#define RADIO_CRCCNF            (* (volatile unsigned long *) 0x40001534)
#define RADIO_CRCINIT           (* (volatile unsigned long *) 0x4000153c)
#define RADIO_CRCPOLY           (* (volatile unsigned long *) 0x40001538)
#define RADIO_CRCSTATUS         (* (volatile unsigned long *) 0x40001400)
#define RADIO_DATAWHITEIV       (* (volatile unsigned long *) 0x40001554)
#define RADIO_DISABLE           (* (volatile unsigned long *) 0x40001010)
#define RADIO_DISABLED          (* (volatile unsigned long *) 0x40001110)
#define RADIO_END               (* (volatile unsigned long *) 0x4000110c)
#define RADIO_FREQUENCY         (* (volatile unsigned long *) 0x40001508)
#define RADIO_INTENSET          (* (volatile unsigned long *) 0x40001304)
#define RADIO_INT_END   3
#define RADIO_IRQ       1
#define RADIO_MODE              (* (volatile unsigned long *) 0x40001510)
#define   RADIO_MODE_NRF_1Mbit 0
#define RADIO_PACKETPTR         (* (volatile unsigned long *) 0x40001504)
#define RADIO_PCNF0             (* (volatile unsigned long *) 0x40001514)
#define RADIO_PCNF0_LFLEN_8 8
#define RADIO_PCNF1             (* (volatile unsigned long *) 0x40001518)
#define RADIO_PREFIX0           (* (volatile unsigned long *) 0x40001524)
#define RADIO_RXADDRESSES       (* (volatile unsigned long *) 0x40001530)
#define RADIO_RXEN              (* (volatile unsigned long *) 0x40001004)
#define RADIO_SHORTS            (* (volatile unsigned long *) 0x40001200)
#define RADIO_START             (* (volatile unsigned long *) 0x40001008)
#define RADIO_TXADDRESS         (* (volatile unsigned long *) 0x4000152c)
#define RADIO_TXEN              (* (volatile unsigned long *) 0x40001000)
#define RADIO_TXPOWER           (* (volatile unsigned long *) 0x4000150c)

#define NVIC_ISER0              (* (volatile unsigned long *) 0xe000e100)
#define NVIC_ICPR0              (* (volatile unsigned long *) 0xe000e280)

#define CLK_HFCLKSTART          (* (volatile unsigned long *) 0x40000000)
#define CLK_HFCLKSTARTED        (* (volatile unsigned long *) 0x40000100)

#define BIT(n) (1UL << (n))
typedef unsigned char byte;
static struct {
    byte length;                /* Packet length, including 3-byte prefix */
    byte version;               /* Version: always 1 */
    byte group;                 /* Radio group */
    byte protocol;              /* Protocol identifier: always 1 */
    byte data[RADIO_PACKET];    /* Payload */
} packet_buffer;

static radio_callback_t rx_callback;

static volatile enum { MODE_RADIO_RX, MODE_RADIO_TX } mode;

static volatile unsigned long interrupt_flag;

/* wait for expected event and clear it */
static void radio_await(unsigned volatile long *event) {
	while (*event == 0)
		;

  *event = 0;
}

/* initialise radio hardware */
void radio_init(radio_callback_t callback) {


    // We need external high-frequency crystal for radio
    CLK_HFCLKSTART = 1;
    while (CLK_HFCLKSTARTED == 0)
        ;

    RADIO_TXPOWER = 0;          // Default transmit power
    RADIO_FREQUENCY = FREQ;     // Transmission frequency
    RADIO_MODE = RADIO_MODE_NRF_1Mbit; // 1Mbit/sec data rate
    RADIO_BASE0 = 0x75626974;   // That spells 'ubit'
    RADIO_TXADDRESS = 0;        // Use address 0 for transmit
    RADIO_RXADDRESSES = BIT(0); //   and also (just one) for receive.

    // Basic configuration
    RADIO_PCNF0 = 8;            // One 8-bit length field
    RADIO_PCNF1 = 0x02040083;	// matched microbian

    // CRC and whitening settings -- match micro_bit runtime
    RADIO_CRCCNF = 2;           // CRC is 2 bytes
    RADIO_CRCINIT = 0xffff;
    RADIO_CRCPOLY = 0x11021;
    RADIO_DATAWHITEIV = 0x18;

    RADIO_PREFIX0 = GROUP;
    RADIO_PACKETPTR = (unsigned long) &packet_buffer;
    
    // Short READY and START to start rx/tx automatically when we enable.
    RADIO_SHORTS = BIT(0);

    rx_callback = callback;
    interrupt_flag = 0;
    mode = MODE_RADIO_RX;

    // Enable interrupt generation for Rx/Tx completion
    RADIO_INTENSET = BIT(RADIO_INT_END);

    // Enable interrupts in NVIC
    NVIC_ISER0 = BIT(RADIO_IRQ);

    // Enable radio and start rx
    RADIO_RXEN = 1;
}

void radio_send(void *buf, unsigned int n) {

    mode = MODE_RADIO_TX;

    // Disable continuous recpetion
    RADIO_DISABLE = 1;
    radio_await(&RADIO_DISABLED);

    // Assemble the packet
    packet_buffer.length = (byte) n+3;
    packet_buffer.version = 1;
    packet_buffer.group = GROUP;
    packet_buffer.protocol = 1;
    memcpy(packet_buffer.data, buf, n);

    // Enable and start Tx
    RADIO_TXEN = 1;
    radio_await(&interrupt_flag);

    // Disable the transmitter -- otherwise it jams the airwaves
    RADIO_DISABLE = 1;
    radio_await(&RADIO_DISABLED);

    // Enable and start Rx
    mode = MODE_RADIO_RX;
    RADIO_RXEN = 1;
}

void RADIO_IRQHandler(void) {

    static char buf[RADIO_PACKET];   // static, not on stack
    int n;

    RADIO_END = 0;

    if (mode == MODE_RADIO_TX)
    {
        interrupt_flag = 1;
        return;
    }

    // Copy only if CRC and groups are okay
    if (RADIO_CRCSTATUS && packet_buffer.group == GROUP)
    {
        // Copy the received packet
        n = packet_buffer.length-3;
        memcpy(buf, packet_buffer.data, n);

        // Call the application callback
        rx_callback(buf, n);
    }

    // Restart reception
    mode = MODE_RADIO_RX;
    RADIO_START = 1;

    return;
}
