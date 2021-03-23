#include "interfaz.h"
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

static double MEM_CHUNK[SIZE];
int main(int argc, char **argv) {
    // Tamaño de la matriz
    int N = (int) atof(argv[1]); argc--; argv++;
    int i,j,k;

    int hilos = (int) atof(argv[1]); argc--; argv++;
    double **a = NULL, **b = NULL, **c = NULL;
    
    // Se reserva de foorma dinamica el espacio de memoria para cada una de las matrices de tamaño NxN
    if ((a = (double **)malloc(N * sizeof(double *)) == NULL ||
    (b = (double **)malloc(N * sizeof(double *))) == NULL ||
    (c = (double **)malloc(N * sizeof(double *))) == NULL) {
        printf("Insuficiente espacio de memoria\n");
        return -1;
    }

    for(i = 0 ; i < N ; i++){
        if ((a[i] = (double **)malloc(N * sizeof(double *))) == NULL ||
            (b[i] = (double **)malloc(N * sizeof(double *))) == NULL ||
            (c[i] = (double **)malloc(N * sizeof(double *))) == NULL) {
            printf("Insuficiente espacio de memoria\n");
            return -1;
        }
    }

    omp_set_num_threads(hilos);

#pragma omp parallel
{
#pragma omp master
    initMatrizDynamic(N,a,b,c);  
    sample_start();
#pragma omp parallel for 
    for (i = 0;i<N;i++){
        for (j = 0;j<N;j++){
            double *auxA,*auxB,suma = 0;
            auxA = *(a+i);
            auxB = *(b+j);
            for (k = 0; k < N; k++, auxA++, auxB++){
                suma += (*auxA * *auxB);
            }
            *(*(c+i)+j) = suma;
        }
    }
    
}
    sample_stop();
    sample_end();
    matrizDynamicFree(N,a,b,c);
    /*
    impresion(N,a);
    printf("\n\n");
    impresion(N,b);
    printf("\n\n");
    impresion(N,c);
    */
    return 0;
}