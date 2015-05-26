#include "timer.h"

//linux system timer, in second
double get_time()
{
  struct timeval tv;
  gettimeofday (&tv, NULL);
  double t = (double)tv.tv_sec+ (double)tv.tv_usec / 1000000;
  return t;
}
unsigned get_time_in_usec()
{
  struct timeval tv;
  gettimeofday (&tv, NULL);
  unsigned t = tv.tv_sec * 1000000 + tv.tv_usec;
  return t;
}

unsigned ccnt_read()
{
	unsigned cc; 
	__asm__ volatile ("mrc p15, 0, %0, c15, c12, 1":"=r" (cc));
	return cc; 
}
