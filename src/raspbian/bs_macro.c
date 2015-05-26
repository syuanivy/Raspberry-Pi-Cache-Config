/* block_size_macro */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

#include "timer.h"

/*
  The program to measure execution time:
  workload:increment n element by 1;
  return: execution time in microseconds;
  parameter:predicted block_size, in words(4 bytes);
  order:access only every other block_size element.
*/
double step_bs(int block_size,int n, int arr[])
{
  int i,last;
  last = n * block_size;//make sure it is within the allocated array

  double start = get_time();
  for(i = 0; i < last; i += block_size){
    arr[i]++;
  }
  double end = get_time();

  double d = (end - start)*1000; //in microseconds
  return d;
}

/*initialize array with 0*/
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
  printf("length of integer arr allocated is %d\n", len);
  int *arr = (int*) malloc(len * sizeof(*arr));

  //Experiment with block_size 2^0 to 2^7 words,(4-512 bytes)
  //increment  n = 10^5 elements by 1 at step of block_size
  double results[8]; //save result for each prediction
  char filename[6] = "bs.csv";
  FILE *f = fopen(filename, "w");
  int b, bs_hypothesis;

  for(b = 0; b < 8; b++){
    bs_hypothesis = (int) exp2(b);//in words
    printf("Hypothesis on block_size--%d bytes:", bs_hypothesis*4);

    set_zero(arr, len);
    results[b] = step_bs(bs_hypothesis,100000,arr);
    printf("%f microseconds;\n", results[b]);
    fprintf(f,"%d,%f\n",bs_hypothesis, results[b]);
  }
  free(arr);
  fclose(f);
}
