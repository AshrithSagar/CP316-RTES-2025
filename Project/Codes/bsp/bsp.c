#include "bsp.h"

void bsp_init(void)
{
    leds_init();
    buttons_init();
    uart_init(UART_RX, UART_TX);
    audio_init(SPEAKER, MIC, RUN_MIC);
    

    return;
}
