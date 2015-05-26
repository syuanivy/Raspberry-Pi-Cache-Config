#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "timer.h"
/* Cache friendly */


//the iteration_add program, cache friendly, return the time difference in seconds
unsigned within_cache(int arr[], int len)
{
  int j;
  unsigned start = get_time_in_usec();
//  printf("start : %f\n", start);

    for(j = 0; j < len; j++){
      arr[j]++;
    }  

  unsigned end = get_time_in_usec();
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

int main(int argc, char **argv){
  //4 KB integer array
  int len = ((int) exp2(10)) *4 /sizeof(int); 
  int arr[len];


 
  set_zero(arr, len); // put the array in cache
  unsigned result = within_cache( arr, len);

  printf("all within cache, execution_time is %u\n", result);

}
