/*
 * Basic IO (mostly output) on BCM2835
 */

#include "bm_io.h"

static unsigned int mini_initialized = 0;
static unsigned int uart_initialized = 0;
static unsigned int scales[] = {
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000,
    2147483649//sentinel
};

//-------------------------------------------------------------------------
// Currently we can only send ascii characters to the UART
// Note: This function definition partially uses the code 
//	 from David Whelch's project.
//-------------------------------------------------------------------------
static void mini_uart_init ( void )
{
    unsigned int ra;
    PUT32(AUX_ENABLES,1);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_CNTL_REG,0);
    PUT32(AUX_MU_LCR_REG,3);
    PUT32(AUX_MU_MCR_REG,0);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_IIR_REG,0xC6);
    PUT32(AUX_MU_BAUD_REG,270);
    ra=GET32(GPFSEL1);
    ra&=~(7<<12); //gpio14
    ra|=2<<12;    //alt5
    ra&=~(7<<15); //gpio15
    ra|=2<<15;    //alt5
    PUT32(GPFSEL1,ra);
    PUT32(GPPUD,0);
    for(ra=0;ra<150;ra++) dummy(ra);
    PUT32(GPPUDCLK0,(1<<14)|(1<<15));
    for(ra=0;ra<150;ra++) dummy(ra);
    PUT32(GPPUDCLK0,0);
    PUT32(AUX_MU_CNTL_REG,3);
    mini_initialized = 1;
}

void uart_init()
{
    // Disable UART0.
    PUT32(UART0_CR, 0x00000000);
    // Setup the GPIO pin 14 && 15.

    int ra = 0;
    // Disable pull up/down for all GPIO pins & delay for 150 cycles.
    PUT32(GPPUD, 0x00000000);
    for(ra=0;ra<150;ra++) dummy(ra);

    // Disable pull up/down for pin 14,15 & delay for 150 cycles.
    PUT32(GPPUDCLK0, (1 << 14) | (1 << 15));
    for(ra=0;ra<150;ra++) dummy(ra);

    // Write 0 to GPPUDCLK0 to make it take effect.
    PUT32(GPPUDCLK0, 0x00000000);

    // Clear pending interrupts.
    PUT32(UART0_ICR, 0x7FF);

    // Set integer & fractional part of baud rate.
    // Divider = UART_CLOCK/(16 * Baud)
    // Fraction part register = (Fractional part * 64) + 0.5
    // UART_CLOCK = 3000000; Baud = 115200.

    // Divider = 3000000 / (16 * 115200) = 1.627 = ~1.
    // Fractional part register = (.627 * 64) + 0.5 = 40.6 = ~40.
    PUT32(UART0_IBRD, 1);
    PUT32(UART0_FBRD, 40);

    // Enable FIFO & 8 bit data transmissio (1 stop bit, no parity).
    PUT32(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

    // Mask all interrupts.
    PUT32(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
	    (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

    // Enable UART0, receive & transfer part of UART.
    PUT32(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));

    uart_initialized = 1;
}


/**
 * send an ascii character to the uart transmitter
 */
void send_ascii(unsigned int c)
{
    if (!uart_initialized) uart_init();
    while ( GET32(UART0_FR) & (1 << 5) ) { }
    PUT32(UART0_DR, c);
}

/**
 * send an ascii character to the mini uart transmitter
 */
void send_ascii_mini(unsigned int c)
{
    if (!mini_initialized) mini_uart_init();
    while(1)
    {
	// poll to make sure the transmitter is idle.
	if(GET32(AUX_MU_LSR_REG)&0x20) break;
    }
    PUT32(AUX_MU_IO_REG,c);
}

/**
 * send a 32-bit unsigned integer
 * in ARM we do not have division...
 */
void send_uint32(unsigned int i)
{
    // deal with negative number
    if (i < 0) {
	send_ascii('-');
	i = -i;
    }
    // input is zero
    if (i == 0) {
	send_ascii('0');
	return;
    }

    // get the scale
    int scale_index = 0;
    while (scales[scale_index] <= i) ++scale_index;
    --scale_index;

    // use an accumulator to get the current digit.
    while (scale_index >= 0) {
	unsigned int accumulator = 0;
	int digit = 0;
	while (accumulator <= (unsigned int)i) {
	    accumulator += scales[scale_index];
	    ++digit;
	}
	digit--;
	accumulator-=scales[scale_index];
	send_ascii(digit+0x30);
	i-=accumulator;
	scale_index--;
    }
}

/**
 * send a zero-terminated c-string
 */
void send_string(const char *str)
{
    for (int i = 0; str[i] != 0; ++i) {
	send_ascii(str[i]);
    }
}
