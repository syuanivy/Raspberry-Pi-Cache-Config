//We are filling 8kb of the cache
//Each loop accesses one block, which is 32 bytes
//That means we need to loop 256 times
//We need to fill each set twice which means 512 loops
#define LOOP_TOTAL 512 

//A block size is assumed to be 32 bytes based on our block size experiment results
#define BLOCK_SIZE 8 //words
