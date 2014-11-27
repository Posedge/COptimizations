#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define ARRSIZE (1 << 27)
#define STEPSIZE 93 //experiment with different numbers here...

int arr[ARRSIZE];
int order[ARRSIZE];

int main(int argc, char **argv)
{
	for(int i = 0; i < ARRSIZE; ++i){
		arr[i] = rand();
	}
	
	unsigned long sum1 = 0, sum2 = 0, sum3 = 0;
	clock_t start_order, end_order, start_random, end_random, start_step, end_step;
    clock_t time_order, time_random, time_step;

	for(int i = 0; i < ARRSIZE; ++i){
		order[i] = i;
	}

    printf("\nstart summing up...\n");
	start_order = clock();
	for(int i = 0; i < ARRSIZE; ++i){
		sum1 += arr[order[i]];
	}
	end_order = clock();
    time_order = end_order - start_order;
	printf("summing up an array of size %d in order took %f seconds.\n", ARRSIZE,
		(double)(time_order) / CLOCKS_PER_SEC);
	
	// perumutate order for summing up
	// might not be perfectly uniform but it will do for measuring spatial locality speedup
	for(int i = 0; i < ARRSIZE; ++i){
		int j = rand() % (ARRSIZE - i) + i;
		int c = order[i];
		order[i] = order[j];
		order[j] = c;
	}
	
    printf("\nstart summing up in random order...\n");
	start_random = clock();
	for(int i = 0; i < ARRSIZE; ++i){
		sum2 += arr[order[i]];
	}
	end_random = clock();
    time_random = end_random - start_random;
	printf("summing up an array of size %d in random order too %f seconds.\n", ARRSIZE,
		(double)time_random / CLOCKS_PER_SEC);
	
    printf("time ratio: %f\n", (double)time_random / time_order);
    
    int index = 0;
    for(int i = 0; i < STEPSIZE; ++i)
        for(int j = i; j < ARRSIZE; j += STEPSIZE)
            order[index++] = j;

    printf("\nstart summing up in steps of %d...\n", STEPSIZE);
    start_step = clock();
    for(int i = 0; i < ARRSIZE; ++i){
		sum3 += arr[order[i]];
	}
    end_step = clock();
    time_step = end_step - start_step;
    printf("summing up an array of size %d in steps of %d took %f seconds.\n", ARRSIZE,
        STEPSIZE, (double)time_step / CLOCKS_PER_SEC);

    printf("time ratio: %f\n", (double)time_step / time_order);

    assert(sum1 == sum2);
    assert(sum1 == sum3);

	return 0;
}
