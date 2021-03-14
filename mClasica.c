/*
 *		Archivo: mClasica.c
 *		Autor: Nicolas Cifuentes Barriga <nicolas.cifuentes01@correo.usa.edu.co>
 *			   Santiago Gutierrez Orjuela <santiago.gutierrez02@correo.usa.edu.co>
 *			   Daniel Siachoque Peralta <daniel.siachoque01@correo.usa.edu.co>
 *			   Guillermo Torres Delgado <juan.torres01@correo.usa.edu.co>
 *      Ultima modificación: Marzo 13, 2021
 *      Sesión: Multiplicación de matrices clásica y transpuesta
 *-----------------------------------------------------------------------------------------------
 *
 *	RESUMEN:
 *	=======
 *	Este programa realiza la multiplicación entre dos matrices de mismas dimensiones. El programa
 *	pide como parametro de ejecución el tamaño para las matrices y la cantidad de hilos para el mismo. 
 *  Luego el programa se encargara por su cuenta de generar dos matrices con numeros semi-aleatorios y 
 *  una tercera de las mismas dimensiones en la cual almacenar el resultado de la multiplicación entre 
 *  estas ultimas.
 *	Finalmente, devolvera el tiempo de ejecución para que el usuario conozca la duración para el
 *  proceso anterior. Todo esto haciendo uso del formato de programación modular (interfaz, modulo y 
 *  aplicación).
 *
 *	NOTA: Al seguir la estructura de programación modular, la definición de las funciones la
 *	encontrara en el archivo modulo.c y el funcionamiento de las mismas en interfaz.h. Asi mismo, se
 *  usan dos principlaes quienes pueden utilizar dichas funciones.
 */

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