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
    double *a,*b,*c;
    a = MEM_CHUNK;
    b = a + N*N;
    c = b + N*N;
    
    omp_set_num_threads(hilos);

#pragma omp parallel
{
#pragma omp master
    initMatriz(N,a,b,c);  
    sample_start();
#pragma omp parallel for 
    for (i = 0;i<N;i++){
        for (j = 0;j<N;j++){
            double *auxA,*auxB,suma = 0;
            auxA = a+(i*N);
            auxB = b+j;
            for (k = 0; k < N; k++, auxA++, auxB+=N){
                suma += (*auxA * *auxB);
            }
            c[i*N+j] = suma;
        }
    }
    
}
    sample_stop();
    sample_end();
    /*
    impresion(N,a);
    printf("\n\n");
    impresion(N,b);
    printf("\n\n");
    impresion(N,c);
    */
    return 0;
}