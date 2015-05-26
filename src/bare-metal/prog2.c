#include <alloca.h>
#include "bm_timer.h"
#include "bm_io.h"

static const size_t ARR_LENGTH = 10 * 1024 *1024;

/*
//the iteration_add program, cache unfriendly, return the time difference in seconds
//based on the result that block size is 8 word
double iter_add_execution(int n, int arr[], int len)
{
  int i,j;
  double start = get_time();
//  printf("start : %f\n", start);
  for(i = 0; i < n; i++){
    for(j = 0; j < len; j+=8){
      arr[j]++;
    }
    for(j = 1; j < len; j+=8){
      arr[j]++;
    }
    for(j = 2; j < len; j+=8){
      arr[j]++;
    }
    for(j = 3; j < len; j+=8){
      arr[j]++;
    }
    for(j = 4; j < len; j+=8){
      arr[j]++;
    }
    for(j = 5; j < len; j+=8){
      arr[j]++;
    }
    for(j = 6; j < len; j+=8){
      arr[j]++;
    }
    for(j = 7; j < len; j+=8){
      arr[j]++;
    }
  }
  double end = get_time();
//  printf("end : %f\n", end);
  double d = end - start;
  return d;
}

*/
//set the values of arr to be 0
void set_zero(int arr[], int len)
{
  int i;
  for(i = 0; i < len; i++ ){
    arr[i] = 0;
  }
}

char ptr[10*1024*1024];
void entrance(int argc, char **argv){
  //a 10MB global integer array
  int len = ARR_LENGTH/4;

  int N = 1;
    for(int k = 0; k < 4; k++){ // for N = 10^0 to 10^5
	set_zero((int *)ptr, len);
	send_string("hang on... when len is ");
	send_uint32(len);
	send_string("\r\n");

//	time = iter_add_execution(N, (int *)ptr, len);
	int i,j;
	unsigned int start = get_timer_tick(CLO);
	unsigned int start64 = get_timer_tick(CHI);
	for(i = 0; i < N; i++) {
	    for(j = 0; j < len; j+=8){
		ptr[j]++;
	    }  
             for(j = 1; j < len; j+=8){
                ptr[j]++;
            }
             for(j = 2; j < len; j+=8){
                ptr[j]++;
            }
             for(j = 3; j < len; j+=8){
                ptr[j]++;
            }
              for(j = 4; j < len; j+=8){
                ptr[j]++;
            }
             for(j = 5; j < len; j+=8){
                ptr[j]++;
            }
             for(j = 6; j < len; j+=8){
                ptr[j]++;
            }
              for(j = 7; j < len; j+=8){
                ptr[j]++;
            }


	}
	unsigned int end = get_timer_tick(CLO);
	unsigned int end64 = get_timer_tick(CHI);

	send_string("for N = ");
	send_uint32(N);
	send_string(", execution_time is HI:");
	send_uint32(end64-start64);
	send_string(" LO:");
	send_uint32(end-start);
	send_string("\r\n");
	N = N*10;  
    }
}
