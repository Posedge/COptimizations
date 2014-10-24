#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

// Too large values here will result in a segmentation fault
#define MSIZE 800

int main(){
  // Matrices as nested arrays
  // Note that these have to be on the stack and of a constant size
  int nested1[MSIZE][MSIZE];
  int nested2[MSIZE][MSIZE];
  int nestedresult[MSIZE][MSIZE];

  // As multi-level arrays
  int **multi1;
  multi1 = (int **)malloc(MSIZE * sizeof(int *));
  int **multi2 = (int **)malloc(MSIZE * sizeof(int *));
  int **multiresult = (int **)malloc(MSIZE * sizeof(int *));
  for(int i = 0; i < MSIZE; ++i){
    multi1[i] = (int *)malloc(MSIZE * sizeof(int));
    multi2[i] = (int *)malloc(MSIZE * sizeof(int));
    multiresult[i] = (int *)malloc(MSIZE * sizeof(int));
  }

  // As dynamically allocated 'nested' arrays
  int *dyn1 = (int *)malloc(MSIZE * MSIZE * sizeof(int));
  int *dyn2 = (int *)malloc(MSIZE * MSIZE * sizeof(int));
  int *dynresult = (int *)malloc(MSIZE * MSIZE * sizeof(int));

  // Fill with random values
  srand(time(NULL)); // randomize
  for(int i = 0; i < MSIZE; ++i){
    for(int j = 0; j < MSIZE; ++j){
      dyn1[MSIZE*i + j] = multi1[i][j] = nested1[i][j] = rand();
      dyn2[MSIZE*i + j] = multi2[i][j] = nested2[i][j] = rand();
    }
  }

  printf("The optimizer is ");
  #ifdef __OPTIMIZE__
  printf("ON.\n");
  #else
  printf("OFF.\n");
  #endif

  // Time matrix multiplication
  clock_t start_nested, end_nested, start_multi, end_multi, start_dyn, end_dyn;

  start_nested = clock();
  // Not sure if putting this in a function is going to convert one array type to something else
  // will try like this first
  for(int m = 0; m < MSIZE; ++m){
    for(int n = 0; n < MSIZE; ++n){
      nestedresult[m][n] = 0;
      for(int i = 0; i < MSIZE; i++){
        nestedresult[m][n] += nested1[m][i] * nested2[i][n];
        // This could be optimized by having a tempory variable for nestedresult[m][n]
        // and setting the actual element at the end to it,
        // but this is about measuring the access speed of an array.
        // The optimizer does that probably anyway
      }
    }
  }
  end_nested = clock();
  printf("nested matrix multiplication of size %dx%d took %f milliseconds.\n", MSIZE, MSIZE, (double)(end_nested - start_nested) / CLOCKS_PER_SEC);

  start_multi = clock();
  for(int m = 0; m < MSIZE; ++m){
    for(int n = 0; n < MSIZE; ++n){
      multiresult[m][n] = 0;
      for(int i = 0; i < MSIZE; i++){
        multiresult[m][n] += multi1[m][i] * multi2[i][n];
      }
    }
  }
  end_multi = clock();
  printf("multilevel matrix multiplication of size %dx%d took %f milliseconds.\n", MSIZE, MSIZE, (double)(end_multi - start_multi) / CLOCKS_PER_SEC);

  start_dyn = clock();
  for(int m = 0; m < MSIZE; ++m){
    for(int n = 0; n < MSIZE; ++n){
      dynresult[MSIZE * m + n] = 0;
      for(int i = 0; i < MSIZE; i++){
        dynresult[MSIZE * m + n] += dyn1[MSIZE * m + i] * dyn2[MSIZE * i + n];
      }
    }
  }
  end_dyn = clock();
  printf("dynamic array matrix multiplication of size %dx%d took %f milliseconds.\n", MSIZE, MSIZE, (double)(end_dyn - start_dyn) / CLOCKS_PER_SEC);

  for(int m = 0; m < MSIZE; ++m){
    for(int n = 0; n < MSIZE; ++n){
      int result = nestedresult[m][n];
      assert(result == multiresult[m][n]);
      assert(result == dynresult[MSIZE * m + n]);
    }
  }

  for(int i = 0; i < MSIZE; ++i){
    free(multi1[i]); free(multi2[i]); free(multiresult[i]);
  }
  free(multi1); free(multi2); free(multiresult);
  free(dyn1); free(dyn2); free(dynresult);
  return 0;
}
