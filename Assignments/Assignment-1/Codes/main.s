	.cpu cortex-m4
	.arch armv7e-m
	.fpu fpv4-sp-d16
	.eabi_attribute 27, 1
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.section	.rodata
	.align	2
	.type	led_rows, %object
	.size	led_rows, 5
led_rows:
	.ascii	"\025\026\017\030\023"
	.align	2
	.type	led_cols, %object
	.size	led_cols, 5
led_cols:
	.ascii	"\034\013\037%\036"
	.text
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.type	gpio_set, %function
gpio_set:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #20
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, [r7, #4]
	cmp	r3, #31
	bgt	.L2
	mov	r3, #1342177280
	b	.L3
.L2:
	ldr	r3, .L6
.L3:
	str	r3, [r7, #12]
	ldr	r3, [r7, #4]
	cmp	r3, #31
	ble	.L4
	ldr	r3, [r7, #4]
	subs	r3, r3, #32
	b	.L5
.L4:
	ldr	r3, [r7, #4]
.L5:
	str	r3, [r7, #4]
	ldr	r3, [r7, #12]
	addw	r3, r3, #1300
	ldr	r2, [r3]
	movs	r1, #1
	ldr	r3, [r7, #4]
	lsl	r3, r1, r3
	ldr	r1, [r7, #12]
	addw	r1, r1, #1300
	orrs	r3, r3, r2
	str	r3, [r1]
	ldr	r3, [r7, #12]
	add	r3, r3, #1288
	mov	r1, r3
	movs	r2, #1
	ldr	r3, [r7, #4]
	lsl	r3, r2, r3
	str	r3, [r1]
	nop
	adds	r7, r7, #20
	mov	sp, r7
	@ sp needed
	ldr	r7, [sp], #4
	bx	lr
.L7:
	.align	2
.L6:
	.word	1342178048
	.size	gpio_set, .-gpio_set
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.type	gpio_clear, %function
gpio_clear:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #20
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, [r7, #4]
	cmp	r3, #31
	bgt	.L9
	mov	r3, #1342177280
	b	.L10
.L9:
	ldr	r3, .L13
.L10:
	str	r3, [r7, #12]
	ldr	r3, [r7, #4]
	cmp	r3, #31
	ble	.L11
	ldr	r3, [r7, #4]
	subs	r3, r3, #32
	b	.L12
.L11:
	ldr	r3, [r7, #4]
.L12:
	str	r3, [r7, #4]
	ldr	r3, [r7, #12]
	addw	r3, r3, #1300
	ldr	r2, [r3]
	movs	r1, #1
	ldr	r3, [r7, #4]
	lsl	r3, r1, r3
	ldr	r1, [r7, #12]
	addw	r1, r1, #1300
	orrs	r3, r3, r2
	str	r3, [r1]
	ldr	r3, [r7, #12]
	addw	r3, r3, #1292
	mov	r1, r3
	movs	r2, #1
	ldr	r3, [r7, #4]
	lsl	r3, r2, r3
	str	r3, [r1]
	nop
	adds	r7, r7, #20
	mov	sp, r7
	@ sp needed
	ldr	r7, [sp], #4
	bx	lr
.L14:
	.align	2
.L13:
	.word	1342178048
	.size	gpio_clear, .-gpio_clear
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.type	led_on, %function
led_on:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	str	r0, [r7, #4]
	str	r1, [r7]
	ldr	r2, .L16
	ldr	r3, [r7, #4]
	add	r3, r3, r2
	ldrb	r3, [r3]	@ zero_extendqisi2
	mov	r0, r3
	bl	gpio_set
	ldr	r2, .L16+4
	ldr	r3, [r7]
	add	r3, r3, r2
	ldrb	r3, [r3]	@ zero_extendqisi2
	mov	r0, r3
	bl	gpio_clear
	nop
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
.L17:
	.align	2
.L16:
	.word	led_rows
	.word	led_cols
	.size	led_on, .-led_on
	.global	m
	.section	.rodata
	.align	2
	.type	m, %object
	.size	m, 4
m:
	.word	7
	.global	c
	.align	2
	.type	c, %object
	.size	c, 4
c:
	.word	5
	.global	x
	.data
	.align	2
	.type	x, %object
	.size	x, 4
x:
	.word	10
	.global	y
	.bss
	.align	2
	.type	y, %object
	.size	y, 4
y:
	.space	4
	.section	.rodata
	.align	2
.LC0:
	.ascii	"hello, world!\012\000"
	.text
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	movs	r2, #7
	ldr	r3, .L20
	ldr	r3, [r3]
	mul	r3, r2, r3
	movs	r2, #5
	add	r3, r3, r2
	ldr	r2, .L20+4
	str	r3, [r2]
	movs	r1, #0
	movs	r0, #0
	bl	led_on
	movs	r1, #6
	movs	r0, #40
	bl	uart_init
	ldr	r0, .L20+8
	bl	uart_puts
	movs	r3, #0
	mov	r0, r3
	pop	{r7, pc}
.L21:
	.align	2
.L20:
	.word	x
	.word	y
	.word	.LC0
	.size	main, .-main
	.ident	"GCC: (Arm GNU Toolchain 12.3.Rel1 (Build arm-12.35)) 12.3.1 20230626"
