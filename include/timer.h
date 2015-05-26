#ifndef _MY_TIMER_H_
#define _MY_TIMER_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

double get_time();
unsigned get_time_in_usec();
unsigned ccnt_read(void);

#endif//_MY_TIMER_H_
