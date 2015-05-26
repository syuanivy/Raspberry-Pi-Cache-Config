#include "bm_timer.h"
#include "bm_io.h"

static int ccnt_initiated = 0;
static int init_ccr(void)
{
	__asm__ volatile ("mcr p15, 0, %0, c15, c12, 0" : : "r" (1));
	send_string("User-level access to CCR has been turned on.\r\n");
	ccnt_initiated = 1;
	return 0;
}
unsigned ccnt_read (void)
{
	if (!ccnt_initiated) init_ccr();
	unsigned cc; 
	__asm__ volatile ("mrc p15, 0, %0, c15, c12, 1":"=r" (cc));
	return cc; 
}

// the current implementation ignores the hi
// 32 bit of the free running timer.
