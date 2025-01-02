/*
 * Minimal system.c file to:
 *  1. Select high frequency clock source using external crystal
 *  2. Enable FPU
 */

#define IOREG32(addr) (*((volatile unsigned long *) (addr)))

/* CoProcessor Access Control Register to enable FPU */
#define CPACR               IOREG32(0xE000ED88UL)

/* Register to select high frequency external crystal */
#define CLK_HFCLKSTART      IOREG32(0x40000000UL)
#define CLK_HFCLKSTARTED    IOREG32(0x40000100UL)

void system_init(void)
{
    /* Enable high accuracy clock */
    CLK_HFCLKSTART = 1;
    while (CLK_HFCLKSTARTED == 0)
        ;

    /* Enable the FPU, by activating coprocessors CP10 and CP11 */
    CPACR |= (3UL << 20) | (3UL << 22);
              /* CP10 */    /* CP11 */
}
