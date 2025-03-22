#ifndef RADIO_H
#define RADIO_H

typedef void (*radio_callback_t)(const char buf[], unsigned int n);
void radio_init(radio_callback_t rx_callback);
void radio_send(void *buf, unsigned int n);

#endif /* RADIO_H */
