#include <stdio.h>
#include "timer.h"
#include "associativity_common.h"
#include "associativity_1way.h"

void read_data(unsigned int *array)
{
    unsigned int loop = 0;
    
    while (loop < LOOP_TOTAL)
    {
        //Read and write data to get it into the cache
        *array = *array + 1;
        
        if (++loop % SETS_TO_FILL == 0)
        {
            //Skip the part of the array to maps to sets that we aren't trying to fill
            array += SKIP_AMOUNT;
        }
        else
        {
            //Go to the next block in the array
            array += BLOCK_SIZE;
        }
    }
}

int main(int argc, char **argv) 
{
    unsigned int array_size = 262144; //1mb - just picking something really large
    unsigned int *array = (unsigned int *)malloc(sizeof(unsigned int) * array_size);
    
    unsigned int purge_array_size = 32 * 1024;
    unsigned int *purge_array = (unsigned int *)malloc(sizeof(unsigned int) * purge_array_size);
    
    //Initialize arrays
    for (int i = 0; i < array_size; i++)
    {
        array[i] = 1;
        if (i < purge_array_size)
        {
            purge_array[i] = 0;
        }
    }

    unsigned int total_time = 0;

    //Run the experiment multiple times and accumulate the reults
    for (int run = 0; run < 10000; run++)
    {
        //Purge the cache before starting the run
        for (int i = 0; i < purge_array_size; i++)
        {
            purge_array[i] = purge_array[i] + 1;
        }

        //Fill the sets with data
        read_data(array);
        
        unsigned int start_time;
        unsigned int end_time;

        //Time reading the same data
        start_time = ccnt_read();
        read_data(array);
        end_time = ccnt_read();
        
        total_time += end_time - start_time;
    }

    free(array);
    free(purge_array);

    printf("N-Way Guess: %u\nTotal time: %u\n", NWAY_GUESS, total_time);

    return 0;
}
