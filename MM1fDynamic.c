#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "interfaz.h"

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    fprintf(stderr, "%s <matrix size> <number of threads>\n", argv[0]);
    return -1;
  }

  int MATRIX_SIZE = atoi(argv[1]);
  argc--;
  argv++;

  int NUM_THREADS = atoi(argv[1]);
  argc--;
  argv++;

  double **matrixA = NULL, **matrixB = NULL, **result = NULL, **transposeMatrixB = NULL;

  if ((matrixA = (double **)malloc(MATRIX_SIZE * sizeof(double *))) == NULL ||
      (matrixB = (double **)malloc(MATRIX_SIZE * sizeof(double *))) == NULL ||
      (transposeMatrixB = (double **)malloc(MATRIX_SIZE * sizeof(double *))) == NULL ||
      (result = (double **)malloc(MATRIX_SIZE * sizeof(double *))) == NULL)
  {
    printf("Not enough memory\n");
    return -1;
  }

  for (int i = 0; i < MATRIX_SIZE; i++)
  {
    if ((matrixA[i] = (double *)malloc(MATRIX_SIZE * sizeof(double))) == NULL ||
        (matrixB[i] = (double *)malloc(MATRIX_SIZE * sizeof(double))) == NULL ||
        (transposeMatrixB[i] = (double *)malloc(MATRIX_SIZE * sizeof(double))) == NULL ||
        (result[i] = (double *)malloc(MATRIX_SIZE * sizeof(double))) == NULL)
    {
      printf("Not enough memory\n");
      return -1;
    }
  }

  omp_set_num_threads(NUM_THREADS); // Sets # of threads to be used
#pragma omp parallel                // Declaration of Open MP pragma
  {

#pragma omp master
    initDynamicMatrixTranspose(MATRIX_SIZE, matrixA, matrixB, result, transposeMatrixB);

    transposeMatrix(MATRIX_SIZE, matrixB, transposeMatrixB);                 // Transpose matrix execution

    sample_start();

    multiplyMatrix(MATRIX_SIZE, matrixA, transposeMatrixB, result);
    
  }
  sample_stop();
  sample_end();
  freeReservedMemoryTranspose(MATRIX_SIZE, matrixA, matrixB, result, transposeMatrixB);
  return 0;
}
