#include "cmsis_os2.h"
#include "bsp.h"

#define N 100000

volatile int count = 0;
volatile int count1 = 0, count2 = 0;
int done1 = 0, done2 = 0;

int nbuf, buf[1000];

void logbuf()
{
    static int done = 0;

    if (!done)
    {
        buf[nbuf++] = count;
        buf[nbuf++] = count1;
        buf[nbuf++] = count2;
    }

    // log once more after both tasks have finished, and then stop.
    if (done1 && done2)
        done = 1;
}

void printbuf()
{
    printf("Tick,count,count1,count2\n");
    for (int i = 0; i < nbuf; i += 3)
        printf("%d,%d,%d,%d\n", i/3, buf[i], buf[i+1], buf[i+2]);
}

void counter1(void *arg)
{
    int i;

    for (i = 0; i < N; i++)
    {
        count++;
        count1++;
        asm("nop");
    }
    done1 = 1;

    printf("[1] count = %d\n", count);
}

void counter2(void *arg)
{
    int i;

    for (i = 0; i < N; i++)
    {
        count++;
        count2++;
        asm("nop");
    }
    done2 = 1;

    printf("[2] count = %d\n", count);

    osDelay(1);
    printbuf();
}

int main(void)
{
    /* Initialiazation */
    bsp_init();

    /* Greetings */
    printf("hello, world!\n");

    /* Initialize and start the kernel */
    osKernelInitialize();

    osThreadNew(counter1, NULL, NULL);
    osThreadNew(counter2, NULL, NULL);

    osKernelStart();
    /* never returns */

    return 0;
}
