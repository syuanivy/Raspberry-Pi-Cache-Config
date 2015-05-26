/**
  * Timer related definitions
  * The timer is running at 1MHz (1 tick/usec)
  * and it is generated from a standalone PLL.
  */

#ifndef _BM_TIMER_
#define _BM_TIMER_

// for model (B+)
#define TIMER_BASE 0x20003000
// address for each register
#define CS		(TIMER_BASE+0x0)
#define CLO		(TIMER_BASE+0x4)
#define CHI		(TIMER_BASE+0x8)
#define C0		(TIMER_BASE+0xC)
#define C1		(TIMER_BASE+0x10)
#define C2		(TIMER_BASE+0x14)
#define C3		(TIMER_BASE+0x18)

/**
  * Simply get the 32 bit of the 
  * free-running timer (1MHz).
  * You need to specify hi or lo
  */
#define get_timer_tick(CLOCK) (GET32(CLOCK))

unsigned ccnt_read(void);

#endif//_BM_TIMER_
