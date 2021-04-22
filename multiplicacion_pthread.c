/*
 *		Archivo: principal.c
 *		Autor: Nicolas Cifuentes Barriga <nicolas.cifuentes01@correo.usa.edu.co> Daniel Julian Siachoque Peralta <daniel.siachoque01@correo.usa.edu.co>
 *		Basado en: Shou Yang <https://github.com/imsure/parallel-programming/blob/master/matrix-multiplication/matrix-mul-pthread.c>
 *		Ultima modificación: Febrero 10, 2021
 *		Sesión: Modulos, compilación separada, archivos Makefile
 *-----------------------------------------------------------------------------------------------------------------------------------------------------
 *
 *	RESUMEN:
 *	=======
 *	Este programa realiza la multiplicación entre dos matrices de mismas dimensiones junto a
 *  la posibilidad de realizarlo a traves de hilos. El programa pide como parametro de ejecución
 *	el tamaño para las matrices y la cantidad de hilos a usar. Luego el programa se encargara
 *	por su cuenta de generar dos matrices con numeros aleatorios y una tercera de las mismas
 *	dimensiones en la cual almacenar el resultado de la multiplicación entre estas ultimas.
 *	Finalmente, devolvera la impresión de las tres matrices para que el usuario conozca tanto los
 *	valores de las matrices generadas como la multiplicación entre estas y la duracion de ejecución
 *	en la multiplicacion. Todo esto haciendo uso del formato de programación modular (interfaz,
 *  modulo y aplicación).
 *
 *	NOTA: Al seguir la estructura de programación modular, la definición de las funciones la
 *	encontrara en el archivo modulo.c y el funcionamiento de las mismas en interfaz.h.
 */

#include "interfaz.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <omp.h>

int main( int argc, char *argv[] ) {

    // Verificación de la cantidad de parametros
    if (argc != 3) {
        fprintf( stderr, "\n%s Dimensiones\t%s Numero de hilos\n", argv[1], argv[2] );
        return -1;
    }

    // Asignación de parametros de entrada
    size = atoi( argv[1] );
    num_threads = atoi( argv[2] );

    // Verificación de la multiplicidad de hilos
    if ( size % num_threads != 0 ) {
        fprintf( stderr, "size %d must be a multiple of num of threads %d\n",
	    size, num_threads );
        return -1;
    }

    // Asignación de las matrices
    matrix1 = allocate_matrix( size );
    matrix2 = allocate_matrix( size );
    matrix3 = allocate_matrix( size );
  
    // Llenado de las matrices
    llenadoA( matrix1, size );
    llenadoB( matrix2, size );

    // Impresion de las matrices aleatorias 
	//printf("Matriz A: \n");
    //impresion( matrix1, size );
	//printf("Matriz B: \n");
	//impresion( matrix2, size );
	//printf("Matriz multiplicacion: \n");

    // Proceso de multiplicación y duración del proceso
    sample_start();
    creacion_hilos();
    sample_stop();

    // Impresion de matriz resultante
    //impresion( matrix3, size );

    // Retorno de la duración de ejecución
	sample_end();
    return 0;
}