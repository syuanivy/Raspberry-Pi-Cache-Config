//Defines were chosen for these parameters so that the values would be compiled into the instructions.
//This was in an effort to reduce data collisions in the cache between the experiment variables
//and the data being accessed in the tests.

#define NWAY_GUESS 1

//The calculation to determine how many sets to fill is as follows
//We assume the cache has 16kb of sets. At 1-way this means there are 512 sets
//We are filling 8kb of data into the sets which means we need to fill 256 sets
//The more general description is
//TOTAL_SETS = CacheSize / (NWAY_GUESS * BlockSize)
//SETS_TO_FILL = TOTAL_SETS / 2 (since we are filling half the cache)
#define SETS_TO_FILL 256 

//The SKIP_AMOUNT is the number of words to skip to skip from the last of the SETS_TO_FILL to get back to the first set
//First the number of sets to skip is determined with TOTAL_SETS - SETS_TO_FILL
//Then this is converted to bytes to skip with (SETS_TO_SKIP + 1) * BLOCK_SIZE
//This takes us back to the address of the first set that we care about
#define SKIP_AMOUNT 2056 // words
