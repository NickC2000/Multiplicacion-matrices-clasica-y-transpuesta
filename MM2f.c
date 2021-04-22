#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "interfaz.h"
static double MEM_CHUNK[SIZE];

int main (int argc, char **argv){
    int N = (int) atof(argv[1]); argc--; argv++;


    int hilos = (int) atof(argv[1]); argc--; argv++;
    double *a,*b,*c;
    double *pA, *pB, c0, c1, c2, c3;

    a = MEM_CHUNK;
    b = a + N*N;
    c = b + N*N;

    int i,j,k;
    omp_set_num_threads(hilos); 

#pragma omp parallel
{
#pragma omp master 
    initMatriz(N,a,b,c);

sample_start();
#pragma omp for

     for(i=0; i<N; i+=2){
        for(j=0; j<N; j+=2){

            c0=c1=c2=c3=0.0;
            pA = a+(i*N); pB = b+(j*N);
            for(k=N; k>0; k-=2, pA+=2, pB+=2){
                double a0, a1, a2, a3;
                double b0, b1, b2, b3;

                a0 = *pA; a1 = *(pA+1); a2 = *(pA+N); a3 = *(pA+N+1);
                b0 = *pB; b1 = *(pB+1); b2 = *(pB+N); b3 = *(pB+N+1);

                c0 += a0*b0 + a1*b1;
                c1 += a0*b2 + a1*b3;
                c2 += a2*b0 + a3*b1;
                c3 += a2*b2 + a3*b3;
            }
            pB = c+i*N+j;
            *pB = c0; *(pB+1)=c1; *(pB+N)=c2; *(pB+N+1)=c3;
        }
        sample_stop();
    }


}
    sample_end();

}
