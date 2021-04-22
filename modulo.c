/*
 *       Archivo: modulo.c
 *       Universidad Sergio Arboleda
 *       Escuela de ingenieria y ciencias exactas
 *       Programas: Ingenieria de sistemas y telecomunicaciones
 *                  Ingenieria electrónica
 *       Autor: Nicolas Cifuentes Barriga <nicolas.cifuentes01@correo.usa.edu.co>
 *			   Santiago Gutierrez Orjuela <santiago.gutierrez02@correo.usa.edu.co>
 *			   Daniel Siachoque Peralta <daniel.siachoque01@correo.usa.edu.co>
 *			   Guillermo Torres Delgado <juan.torres01@correo.usa.edu.co>
 *       Ultima modificación: Marzo 13, 2021
 *       Sesión: Multiplicación de matrices clásica y transpuesta
 *-----------------------------------------------------------------------------------------------
 *
 *      RESUMEN:
 *      =======
 *      Este fichero de la aplicación (principal.c) presenta la vinculación con la interfaz
 *	    (interfaz.h) presentando las funciones completamente desarrolladas para su implementación
 *	    en los procesos presentes en la aplicación.
 *
 *      NOTA: Al seguir la estructura de programación modular, el funcionamiento de las funciones
 *      los encontrara en el fichero interfaz.h y el llamado de las mismas en principal.c
 */

#include "interfaz.h"
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

struct timeval start, end; //Structura para la toma de tiempo

void sample_start(){
	gettimeofday(&start,NULL); //Toma el tiempo de inicio de ejecución
}
void sample_stop(){
	gettimeofday(&end,NULL); //Toma el tiempo de final de ejecución
}
void sample_end(){ //Se presenta el calculo en microsegundos
	printf("%ld\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
}

void initMatrizDynamic(int N,double **A,double **B,double **C){
    int i,j; //Variables de iterazión
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            *(*(A+j)+i) = 3.1*(j-i); //Genera dato en la matriz A
            *(*(B+j)+i) = 4.1*(j+i); //Genera dato en la matriz B
            *(*(C+j)+i) = 5.1;       //Genera dato en la matriz C los cuales seran alterados en la multiplicación
        }
    }
}

void matrizDynamicFree(int N,double **A,double **B,double **C){
    int i; //Variable de iterazión
#pragma omp parallel for
    for (i = 0; i < N; i++){
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}

void initMatriz(int N,double *A,double *B,double *C){
    int i,j; //Variables de iterazión
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            A[j+i*N] = 3.1*(j-i); //Genera dato en la matriz A
            B[j+i*N] = 4.1*(j+i); //Genera dato en la matriz B
            C[j+i*N] = 5.1;       //Genera dato en la matriz C los cuales seran alterados en la multiplicación
        }
    }
}

void initTranspose(int N,double *B,double *T){
    int i,j; //Variables de iterazión
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            T[j+i*N] = B[i+j*N]; //Genera la transpuesta de la matriz B
        }
    }
}

void initDynamicMatrixTranspose(int MATRIX_SIZE, double **matrixA, double **matrixB, double **result, double **transposeMatrixB){
  int i, j;
  for (i = 0; i < MATRIX_SIZE; i++)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
    {
      *(*(matrixA + j) + i) = 2.01 * (i + j);
      *(*(matrixB + j) + i) = 3.01 * (i - j);
      *(*(transposeMatrixB + j) + i) = 5.01;
      *(*(result + j) + i) = 5.01;
    }
  }
}

void impresion(int N, double *matriz){
    int i,j; //Variables de iterazión
    if(N <= 4){
        for (i = 0;i<N;i++){
            for (j = 0;j<N;j++){
                printf("%f \t",matriz[j+i*N]); //Imprime el valor en la casilla
            }
            printf("\n");
        }
    }
}

void multiplyMatrix(int MATRIX_SIZE, double **matrixA, double **matrixB, double **result){
  int i, j, k;
#pragma omp for // Open MP pragma for declaration for parallelism
  for (i = 0; i < MATRIX_SIZE; i++)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
    {
      double *auxMatrixA, *auxMatrixB; // Auxiliary Pointers to matrixes (Array) positions
      double sum = 0.0;

      // auxMatrixA = *(matrixA + (i * MATRIX_SIZE)); // Assignment of the position of the matrixA in the main array for looping in it
      auxMatrixA = *(matrixA + i); // Assignment of the position of the matrixA in the main array for looping in it
      auxMatrixB = *(matrixB + j); // Assignment of the position of the matrixB in the main array for looping in it

      for (k = 0; k < MATRIX_SIZE; k++, auxMatrixA++, auxMatrixB++) // Increasing of the position of the pointers to matrixes
      // for (k = MATRIX_SIZE; k > 0; k--, auxMatrixA++, auxMatrixB++) // Increasing of the position of the pointers to matrixes
      {
        sum += (*auxMatrixA * *auxMatrixB);
      }
      *(*(result + j) + i) = sum; // Assignment of sum to the result section of the main array
    }
  }
}

void transposeMatrix(int MATRIX_SIZE, double **matrix, double **transpose){
  int i, j;
#pragma omp for // Open MP pragma for declaration for parallelism
  for (i = 0; i < MATRIX_SIZE; i++)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
    {
      *(*(transpose + j) + i) = *(*(matrix + i) + j);
      // transpose[(j * MATRIX_SIZE) + i] = matrix[j + i * MATRIX_SIZE]; // Assignment of matrix transpose to the transpose matrix
    }
  }
}

void freeReservedMemoryTranspose(int MATRIX_SIZE, double **matrixA, double **matrixB, double **result, double **transpose){

  int i;

#pragma omp parallel for
  for (i = 0; i < MATRIX_SIZE; i++)
  {
    free(matrixA[i]);
    free(matrixB[i]);
    free(result[i]);
    free(transpose[i]);
  }
  free(matrixA);
  free(transpose);
  free(matrixB);
  free(result);
}

int ** allocate_matrix( int size ) {

    int * vals = (int *) malloc( size * size * sizeof(int) );
    int ** ptrs = (int **) malloc( size * sizeof(int*) );

    int i;
    for (i = 0; i < size; ++i) {
        ptrs[ i ] = &vals[ i * size ];
    }

    return ptrs;
}

void llenadoA( int **matrix, int size ){
    int i,j;
   	time_t t;
	srand((unsigned) time (&t));
    for (i = 0 ;  i < size ; i++){
        for (j = 0 ; j < size ; j++){
            matrix[i][j] = rand()%11;
        }
    }
}
void llenadoB( int **matrix, int size ){
    int i,j;
    for (i = 0 ;  i < size ; i++){
	    for (j = 0 ; j < size ; j++){
            matrix[i][j] = rand()%11;
        }
    }
}
void *multiplicacionPthread( void *arg ) {
    int i, j, k, tid, portion_size, row_start, row_end;
    int sum;
  
    tid = *(int *)(arg);
    portion_size = size / num_threads;
    row_start = tid * portion_size;
    row_end = (tid+1) * portion_size;

    for (i = row_start; i < row_end; ++i) { 
        for (j = 0; j < size; ++j) { 
            sum = 0;
            for (k = 0; k < size; ++k) { 
	            sum += matrix1[ i ][ k ] * matrix2[ k ][ j ];
            }
            matrix3[ i ][ j ] = sum;
        }
    }
	pthread_exit(NULL);
}
void creacion_hilos(){
	int i;
	pthread_t * threads;
	threads = (pthread_t *) malloc( num_threads * sizeof(pthread_t) );
	for ( i = 0; i < num_threads; ++i ) {
        int *tid;
        tid = (int *) malloc( sizeof(int) );
        *tid = i;
        pthread_create( &threads[i], NULL, multiplicacionPthread, (void *)tid );
    }
	for ( i = 0; i < num_threads; ++i ) {
        pthread_join( threads[i], NULL );
    }
}