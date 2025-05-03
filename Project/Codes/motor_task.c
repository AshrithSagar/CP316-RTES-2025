#include <stdint.h>

#include "bsp/bsp.h"
#include "bsp/microbit.h"
#include "bsp2/bsp2.h"
#include "rtx/cmsis_os2.h"

#define M1A P0
#define M1B P1
#define M2A P2
#define M2B P16

int motor_task(void) {
    uart_puts("hello, motors!\n");
    audio_sweep(100, 8000, 200);

#if 0
    osDelay(10);   // let LSM chip boot up
    LSM303AGR_Init(I2C_SCL, I2C_SDA);
#endif

    printf("FF\n");
    motor_init(M1A, M1B, M2A, M2B);
    motor_on(MOTOR_FORWARD, 50, MOTOR_FORWARD, 50);
    osDelay(1000);

    printf("FR\n");
    motor_on(MOTOR_FORWARD, 50, MOTOR_REVERSE, 50);
    osDelay(1000);

    printf("RF\n");
    motor_on(MOTOR_REVERSE, 50, MOTOR_FORWARD, 50);
    osDelay(1000);

    printf("RR\n");
    motor_on(MOTOR_REVERSE, 50, MOTOR_REVERSE, 50);
    osDelay(1000);
    motor_off();

    audio_sweep(100, 8000, 200);
    osDelay(100);
    audio_sweep(100, 8000, 200);
    osDelay(100);

    while (1) {
#if 0
        int16_t xyz[3], max = 0, maxmax = 0;

        LSM303AGR_AccReadXYZ(xyz);
        printf("%d\t%d\t%d\n", xyz[0], xyz[1], xyz[2]);

#define THRESHOLD 32000
        if ((xyz[0] > 32000) || (xyz[0] < -32000) ||
            (xyz[1] > 32000) || (xyz[1] < -32000) ||
            (xyz[2] > 32000) || (xyz[2] < -32000))
        {
            max = (xyz[0] > xyz[1])
                    ? ((xyz[0] > xyz[2]) ? xyz[0] : xyz[2])
                    : ((xyz[1] > xyz[2]) ? xyz[1] : xyz[2]);
            if (max > maxmax)
                maxmax = max;
            printf("knock (max = %d/%d)!\n", max, maxmax);
            audio_sweep(2000, 500, 200);
        }
        // debug / calibrate
        // printf("%d\t%d\t%d\n", xyz[0], xyz[1], xyz[2]);
#endif
    }

    return 0;
}
