/* capacity_macro */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "timer.h"

/*
  The program to measure execution time:
  workload:increment each element by 1 for n loops;
  return: execution time in microseconds;
  parameter:predicted cache capacity, in words(4 bytes);
  order: normal order.
*/
double iter_add_full(int n, int arr[], int capacity)
{
  int i, loop;

  double d, start, end;
  for(loop = 0; loop < n; loop++ ){
    start = get_time();
    for(i = 0; i < capacity; i += 8 ){ // to have same number of inner loops
    arr[i]++;
    }
    end = get_time();
    d += (end - start) * 1000;
  }
  return d;
}


double iter_add_half(int n, int arr[], int half)
{
  int i, loop;

  double d, start, end;
  for(loop = 0; loop < n; loop++ ){
    start = get_time();
    for(i = 0; i < half; i += 8 ){
     arr[i]++;
    }
    for(i = 0; i < half; i+= 8){
     arr[i]++;
    }
    end  = get_time();
    d += (end -start) * 1000;
  }
  return d;
}


/*initialize array with 0*/
void set_zero_reverse(int arr[], int len)
{
  int i;
  for(i = len-1 ; i >= 0 ; i-- ){ //reverse purging the array, so that the first half is in cache
    arr[i] = 0;
  }
}

 int main(int argc, char **argv){
  //Experiment capacity from 16KB(2^12 words) down to 1KB(2^8 words), 5 sampling points
  //loop until the the array has done 2^13 total increments by 1;
  int c, capacity, n;
  n = (int) exp2(15);

  //save result for each prediction
  double results[8][3]; //rows are different capacity, columns are time for first half and the whole

  for(c = 15; c >=8; c--){
    capacity = (int) exp2(c);
    results[c-8][0] = exp2(c-8);//in kb

    int *arr = (int*) malloc(capacity * sizeof(*arr));

    set_zero_reverse(arr, capacity);
    results[c-8][1] = iter_add_half(n, arr, capacity/2);
    set_zero_reverse(arr, capacity);
    results[c-8][2] = iter_add_full(n, arr, capacity);
    printf("Hypothesis on capacity--%f KB: %f, %f\n", results[c-8][0], results[c-8][1], results[c-8][2]);
    free(arr);
  }
  //write results into a csv file;
  char filename[12] = "capacity.csv";
  FILE *f = fopen(filename, "w"); 
  int i;
  for (i = 0; i < 8; i++) { 
    fprintf(f, "%f, %f, %f\n", results[i][0], results[i][1], results[i][2]);
  } 
  fclose(f); 

}
