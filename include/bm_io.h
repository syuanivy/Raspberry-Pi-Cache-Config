/*
 * Some constant definition
 */

#ifndef _BM_IO_
#define _BM_IO_

// function declarations for basic routine
extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern unsigned int dummy ( unsigned int );

void send_ascii(unsigned int c);
void send_uint32(unsigned int i);
void send_uint64(unsigned long long i);
void send_string(const char *str);

// since we are dealing with BCM2835 (B+)
// Note: This part uses the code from dwhelch's raspberry project.
#define PBASE		0x20000000

#define GPFSEL1         (PBASE+0x00200004)
#define GPSET0          (PBASE+0x0020001C)
#define GPCLR0          (PBASE+0x00200028)
#define GPPUD           (PBASE+0x00200094)
#define GPPUDCLK0       (PBASE+0x00200098)
// Those fields are used for mini-uart(which is not supported in QEMU)
#define AUX_ENABLES     (PBASE+0x00215004)
#define AUX_MU_IO_REG   (PBASE+0x00215040)
#define AUX_MU_IER_REG  (PBASE+0x00215044)
#define AUX_MU_IIR_REG  (PBASE+0x00215048)
#define AUX_MU_LCR_REG  (PBASE+0x0021504C)
#define AUX_MU_MCR_REG  (PBASE+0x00215050)
#define AUX_MU_LSR_REG  (PBASE+0x00215054)
#define AUX_MU_MSR_REG  (PBASE+0x00215058)
#define AUX_MU_SCRATCH  (PBASE+0x0021505C)
#define AUX_MU_CNTL_REG (PBASE+0x00215060)
#define AUX_MU_STAT_REG (PBASE+0x00215064)
#define AUX_MU_BAUD_REG (PBASE+0x00215068)

// The base address for UART.
#define UART0_BASE	0x20201000

// The offsets for reach register for the UART.
#define UART0_DR	(UART0_BASE + 0x00)
#define UART0_RSRECR	(UART0_BASE + 0x04)
#define UART0_FR	(UART0_BASE + 0x18)
#define UART0_ILPR	(UART0_BASE + 0x20)
#define UART0_IBRD	(UART0_BASE + 0x24)
#define UART0_FBRD	(UART0_BASE + 0x28)
#define UART0_LCRH	(UART0_BASE + 0x2C)
#define UART0_CR	(UART0_BASE + 0x30)
#define UART0_IFLS	(UART0_BASE + 0x34)
#define UART0_IMSC	(UART0_BASE + 0x38)
#define UART0_RIS	(UART0_BASE + 0x3C)
#define UART0_MIS	(UART0_BASE + 0x40)
#define UART0_ICR	(UART0_BASE + 0x44)
#define UART0_DMACR	(UART0_BASE + 0x48)
#define UART0_ITCR	(UART0_BASE + 0x80)
#define UART0_ITIP	(UART0_BASE + 0x84)
#define UART0_ITOP	(UART0_BASE + 0x88)
#define UART0_TDR	(UART0_BASE + 0x8C)

#endif//_BM_IO_
