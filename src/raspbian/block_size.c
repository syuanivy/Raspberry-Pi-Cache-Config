#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
/* block_size */

#include "timer.h"
//the iteration_add program, return the time difference in seconds
//make predicted block size a parameter
double iter_add_execution(int n, int block_size, int arr[], int len)
{
  //printf("N = %d, block_size = %d, len = %d\n", n, block_size, len);
  int i,j,k;

  double start = get_time();
  for(i = 0; i < n; i++){
    for(k = 0; k < block_size; k++){
      for(j = 0; j < len; j += block_size){
        arr[j + k]++;
      }
    }  
  }
  
  double end = get_time();
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
   //a 100MB global integer array
  int len = ((int) exp2(20)) * 100 /sizeof(int); 
  printf("length of arr is %d\n", len);
  int *arr = (int*) malloc(len * sizeof(*arr));

  //Experiment with block_size 2^0 to 2^4 words
  double results[8][7]; //rows are different block_size, cols are different N

  int i, b, bs_hypothesis, N;

  for(b = 0; b < 8; b++){
    bs_hypothesis = (int) exp2(b);
    printf("block_size hypothesis %d: ", bs_hypothesis);
    for(i = 0; i < 7; i++){ // i<7 eventually
      N = (int) pow(10, i);  
      set_zero(arr, len);
      results[b][i] = iter_add_execution(N, bs_hypothesis, arr, len);
      printf("%f seconds   ;   ", results[b][i]);
    }
    printf("\n");
  }

  

  free(arr);

}
