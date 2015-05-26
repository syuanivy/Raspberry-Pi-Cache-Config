#include "bm_timer.h"
#include "bm_io.h"
//the iteration_add program, cache friendly, return the time difference in seconds


unsigned within_cache(int arr[], int len)
{
  int j;
  unsigned start = get_timer_tick(CLO);
//  printf("start : %f\n", start);

    for(j = 0; j < len; j++){
      arr[j]++;
    }  

  unsigned end = get_timer_tick(CLO);
//  printf("end : %f\n", end);
  unsigned d = end - start;
  return d;
}

//set the values of arr to be 0
void set_zero(int arr[], int len)
{
  int i;
  for(i = 0; i < len; i++ ){
    arr[i] = 0;
  }
}

void entrance(int argc, char **argv){
  //4 KB integer array
  int len = 1024; 
  int arr[len];


 
  set_zero(arr, len); // put the array in cache
  unsigned result = within_cache( arr, len);

  send_string("all within cache, execution_time is ");
  send_uint32(result);

}
