#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "timer.h"
/* Cache friendly */


//the iteration_add program, cache friendly, return the time difference in seconds
double iter_add_execution(int n, int arr[], int len)
{
  int i,j,k;
  double start = get_time_in_usec();
//  printf("start : %f\n", start);
  for(i = 0; i < n; i++){
    for(k = 1; k < (len/4096)+1; k++){
      for(j = (k-1)*4096; j < k*4096; j++){
        arr[j]++;
      }  
    } 
  }
  double end = get_time_in_usec();
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
  char filename[8] = "fast.csv";
  FILE *f = fopen(filename,"w");

  int i, N;
  for(i = 0; i < 5; i++){ // for N = 10^0 to 10^4
    N = (int) pow(10, i);  
    set_zero(arr, len);
    results[i] = iter_add_execution( N, arr, len);

    printf("for N = %d, execution_time is %f\n", N, results[i]);
    fprintf(f,"%d, %f\n", N, results[i]);
  }

  free(arr);
  fclose(f);

}

