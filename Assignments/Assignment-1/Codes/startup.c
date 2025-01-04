#include <stdint.h>

/* Stack */
#define STACK_SIZE  8192
__attribute__ ((section(".stack"))) // place in .stack section
uint8_t stack_mem[STACK_SIZE];      // should be aligned to 8-byte boundary
                                    //   in the linker command file

/* Prototypes */
void Reset_Handler(void);
static void crt_init(void);     // C run-time initialization
extern int system_init(void);   // system initialization
extern int main(void);          // application main
void Default_Handler(void);     // common handler for all unused exceptions

/* Vector table */
typedef void (*pfn_t)(void);

__attribute__ ((section(".vectors")))
pfn_t vector_table[] =
{
    /* Core exceptions */
    (pfn_t)(long)(stack_mem + STACK_SIZE),  // initial stack pointer
    Reset_Handler,                          // The reset handler
    Default_Handler,                        // NMI_Handler
    Default_Handler,                        // HardFault_Handler
    Default_Handler,                        // MPUFault_Handler
    Default_Handler,                        // BusFault_Handler
    Default_Handler,                        // UsageFault_Handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    Default_Handler,                        // SVC_Handler
    Default_Handler,                        // DebugMonitor_Handler
    0,                                      // Reserved
    Default_Handler,                        // PendSV_Handler
    Default_Handler,                        // SysTick_Handler

    /* Peripheral interrupts */
    Default_Handler,        // POWER_CLOCK_IRQHandler
    Default_Handler,        // RADIO_IRQHandler,
    Default_Handler,        // UARTE0_UART0_IRQHandler
    Default_Handler,        // SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler
    Default_Handler,        // SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler
    Default_Handler,        // NFCT_IRQHandler
    Default_Handler,        // GPIOTE_IRQHandler
    Default_Handler,        // SAADC_IRQHandler
    Default_Handler,        // TIMER0_IRQHandler
    Default_Handler,        // TIMER1_IRQHandler
    Default_Handler,        // TIMER2_IRQHandler
    Default_Handler,        // RTC0_IRQHandler
    Default_Handler,        // TEMP_IRQHandler
    Default_Handler,        // RNG_IRQHandler
    Default_Handler,        // ECB_IRQHandler
    Default_Handler,        // CCM_AAR_IRQHandler
    Default_Handler,        // WDT_IRQHandler
    Default_Handler,        // RTC1_IRQHandler,
    Default_Handler,        // QDEC_IRQHandler
    Default_Handler,        // COMP_LPCOMP_IRQHandler
    Default_Handler,        // SWI0_EGU0_IRQHandler
    Default_Handler,        // SWI1_EGU1_IRQHandler
    Default_Handler,        // SWI2_EGU2_IRQHandler,
    Default_Handler,        // SWI3_EGU3_IRQHandler
    Default_Handler,        // SWI4_EGU4_IRQHandler
    Default_Handler,        // SWI5_EGU5_IRQHandler
    Default_Handler,        // TIMER3_IRQHandler
    Default_Handler,        // TIMER4_IRQHandler
    Default_Handler,        // PWM0_IRQHandler
    Default_Handler,        // PDM_IRQHandler
    0,                      // Reserved
    0,                      // Reserved
    Default_Handler,        // MWU_IRQHandler
    Default_Handler,        // PWM1_IRQHandler
    Default_Handler,        // PWM2_IRQHandler
    Default_Handler,        // SPIM2_SPIS2_SPI2_IRQHandler
    Default_Handler,        // RTC2_IRQHandler
    Default_Handler,        // I2S_IRQHandler
    Default_Handler,        // FPU_IRQHandler
    Default_Handler,        // USBD_IRQHandler
    Default_Handler,        // UARTE1_IRQHandler
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    Default_Handler,        // PWM3_IRQHandler
    0,                      // Reserved
    Default_Handler,        // SPIM3_IRQHandler
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0                       // Reserved
};

void Reset_Handler(void)
{
    crt_init();
    system_init();
    main();

    while (1)
        ;   // loop forever
}

/* Default exception handler */
void Default_Handler(void)
{
    while (1)
        ;
}

/*****************************************************************************
 * Symbols created by the linker
 *****************************************************************************/
extern uint32_t __data_load__;  // load address of initialized data in ROM
extern uint32_t __data_start__; // start address of initialized data in RAM
extern uint32_t __data_end__;   // end address of initialized data in RAM
extern uint32_t __bss_start__;  // start address of uninitialized data in RAM
extern uint32_t __bss_end__;    // end address of uninitialized data in RAM
extern uint32_t __stack_end__;  // address of stack end in RAM

static void crt_init(void)
{
    uint32_t *src, *dst;

    // Copy the data segment initializers from flash to SRAM.
    src = &__data_load__;
    dst = &__data_start__;
    while(dst < &__bss_start__)
        *dst++ = *src++;

    // Zero fill the bss segment.
    for(dst = &__bss_start__; dst < &__bss_end__; dst++)
        *dst = 0;

    return;
}
