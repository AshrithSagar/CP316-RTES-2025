#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "bsp.h"

#include "cmsis_os2.h"

extern void motor_task(void *arg);

/* OS objects */
osThreadId_t tid1, tid2;

#define MAX_COUNT 100

void task1(void *arg)
{
    uint32_t r, c;
    uint32_t r0, c0;
    int count;

    printf("hello, task1!\n");

    r = 0; c = 0;
    r0 = 0; c0 = 1;

    while (1)
    {
        for (count = 0; count < MAX_COUNT; count++)
        {
            frame_buffer[r][c] = 1;
            osDelay(50);
            frame_buffer[r][c] = 0;

            r += r0;
            c += c0;

            if ((r == 0) && (c == 0))
            {
                c0 = 1; r0 = 0;
            }
            else if ((r == 0) && ((c == (LED_NUM_COLS - 1))))
            {
                c0 = 0; r0 = 1;
            }
            else if ((r == (LED_NUM_ROWS - 1)) && ((c == (LED_NUM_COLS - 1))))
            {
                c0 = -1; r0 = 0;
            }
            else if ((r == (LED_NUM_ROWS - 1)) && (c == 0))
            {
                c0 = 0; r0 = -1;
            }
        }
    }
}

void task2(void *arg)
{
    uint32_t r, c;
    uint32_t r0, c0;

    printf("hello, task2!\n");

    r = 1; c = 1;
    r0 = 0; c0 = 1;

    while (1)
    {
        frame_buffer[r][c] = 1;
        osDelay(50);
        frame_buffer[r][c] = 0;

        r += r0;
        c += c0;

        if ((r == 1) && (c == 1))
        {
            c0 = 1; r0 = 0;
        }
        else if ((r == 1) && ((c == (LED_NUM_ROWS - 2))))
        {
            c0 = 0; r0 = 1;
        }
        else if ((r == (LED_NUM_COLS - 2)) && ((c == (LED_NUM_ROWS - 2))))
        {
            c0 = -1; r0 = 0;
        }
        else if ((r == (LED_NUM_COLS - 2)) && (c == 1))
        {
            c0 = 0; r0 = -1;
        }
    }
}

void task3(void *arg)
{
    int toggle1 = 0, toggle2 = 0;

    printf("hello, task3!\n");

    while (1)
    {
        frame_buffer[2][2] ^= 1;
        osDelay(100);

        if (button_get(0))
        {
            osDelay(25);
            while (button_get(0))
                ;

            if (toggle1)
                osThreadResume(tid1);
            else
                osThreadSuspend(tid1);

            toggle1 = !toggle1;
        }

        if (button_get(1))
        {
            osDelay(25);
            while (button_get(1))
                ;

            if (toggle2)
                osThreadResume(tid2);
            else
                osThreadSuspend(tid2);

            toggle2 = !toggle2;
        }
    }
}

void app_main(void *arg)
{
    osTimerId_t timer_id;
    osThreadId_t tid;

    /* runner tasks */
    tid1 = osThreadNew(task1, NULL, NULL);
    tid2 = osThreadNew(task2, NULL, NULL);

    /* controller tasks */
    tid = osThreadNew(task3, NULL, NULL);
    osThreadSetPriority(tid, osPriorityHigh - 1);

    /* refresh timer */
    timer_id = osTimerNew ((void *) led_row_refresh, osTimerPeriodic, NULL, NULL);
    osTimerStart (timer_id, 5);
}

void board_init(void)
{
    leds_init();
    buttons_init();
    uart_init(UART_RX, UART_TX);
    audio_init(SPEAKER, MIC, RUN_MIC);

    return;
}

int main(void)
{
    /* Initialiazation */
    board_init();

    /* Greetings */
    printf("hello, world!\n");
    audio_sweep(100, 2000, 200);

    /* Initialize and start the kernel */
    osKernelInitialize();
    osThreadNew(motor_task, NULL, NULL);
    osKernelStart();
    /* never returns */

    led_blink(2, 2);

    return 0;
}
