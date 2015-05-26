#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "timer.h"
/* Cache unfriendly */


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

//set the values of arr to be 0
void set_zero(int arr[], int len)
{
  int i;
  for(i = 0; i < len; i++ ){
    arr[i] = 0;
  }
}

int main(int argc, char **argv){
  //a 10MB global integer array
  int len = ((int) exp2(20)) * 10 /sizeof(int);
  printf("length of arr is %d\n", len);
  int *arr = malloc(len * sizeof(*arr));

  //array to save the results for N = 10^0 to 10^4
  //too slow for N>= 10^5
  double results[5];

  char filename[8] = "slow.csv";
  FILE *f = fopen(filename,"w");
  
  int i, N;
  for(i = 0; i < 4; i++){ // for N = 10^0 to 10^4
    N = (int) pow(10, i);  
    set_zero(arr, len);
    results[i] = iter_add_execution( N, arr, len);

    printf("for N = %d, execution_time is %f\n", N, results[i]);
    fprintf(f,"%d, %f\n", N, results[i]);
  }

  free(arr);
  fclose(f);

}

