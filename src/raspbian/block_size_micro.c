#include <stdio.h>
#include "timer.h"

#define CACHE_SIZE 4096 //words
#define MAX_BLOCKSIZE_GUESS 64 //words
#define BLOCK_TEST_RUNS 100 //how many times to run the test

int purgeArray[CACHE_SIZE] = { 0 };
int accessArray[MAX_BLOCKSIZE_GUESS] = { 0 };
unsigned int totalRunTimes[MAX_BLOCKSIZE_GUESS] = { 0 };

void runBlockSizeTest() {

    //Repeat the test many times to reduce the influence of noise on any given test
    for (int i = 0; i < BLOCK_TEST_RUNS; i++) {

        //Measure the time to access a portion of the array
        for (int j = 1; j < MAX_BLOCKSIZE_GUESS; j++) {

            //Purge the data cache
            int read;
            for (int i = 0; i < CACHE_SIZE; i++) {
                read = purgeArray[i];
            }

            //Load one block into the cache
            read = accessArray[0];

            //Time how long it takes to access the subset of elements 
	    unsigned int startTime = ccnt_read();
	    for (int k = 0; k < j; k++) {
	        read = accessArray[k];
	    }
	    printf("read: %d\n", read);
	    totalRunTimes[j] = totalRunTimes[j] + ccnt_read() - startTime;
	}
    }

    //Print the results
    for (int i = 1; i < MAX_BLOCKSIZE_GUESS; i++) {
	printf("%u\n", totalRunTimes[i]);
    }
}

int main(int argc, char *argv[]) {
    runBlockSizeTest();
    return 0;
}
