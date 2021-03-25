/*
 *       Archivo: interfaz.h
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
 *      Este fichero para el programa principal (principal.c) hace la labor de interfaz, tiene
 *	    por lo general definiciones, constantes y prototipos de las funciones que presentara la
 *	    aplicación.
 *
 *	    NOTA: Al seguir la estructura de programación modular, la definición de las funciones
 *      las encontrara en el fichero modulo.c y el llamado de las mismas en principal.c
 *
 *	    Función: sample_start
 *	    Uso: sample_start()
 *	    --------------------------------
 *	    Inicia un conteo referente a la hora local
 *	    con la cual se realizara calculo de duración
 *      posteriormente.
 *
 *	    Función: sample_stop
 *	    Uso: sample_stop()
 *	    --------------------------------
 *	    Finaliza el conteo referente a la hora local
 *	    con la cual se realizara calculo de duración
 *      posteriormente.
 *
 *	    Función: sample_end
 *	    Uso: sample_end()
 *	    --------------------------------
 *	    Retorna la duración de ejecución tomada por
 *	    la ejecucion en la multiplicación gracias a
 *      las funciones previamente mencionadas, esto
 *      en milisegundos.
 *
 *      Función: initMatriz
 *	    Uso: initMatriz(int N,double *A,double *B,double *C)
 *	    --------------------------------
 *	    Inicializa tres matrices A, B, C con,
 *      dimensiones N, valores semi-aleatorios. Cabe
 *      recalcar que los valores de C seran alterados
 *      
 *      Función: initTranspose
 *	    Uso: initTranspose(int N,double *B,double *T)
 *	    --------------------------------
 *	    Toma la matriz B con dimensiones N y crea la
 *      matriz T siendoo transpuesta de la primera
 *      
 *      Función: impresion
 *	    Uso: impresion(int N, double *matriz)
 *	    --------------------------------
 *      Imprime la matriz que reciba como parametro
 *	    de dimensiones N
 */

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

/*Prototypes for the functions*/
#define SIZE (1024*1024*60*3)
void sample_start();
void sample_stop();
void sample_end();
void initMatrizDynamic(int N,double **A,double **B,double **C);
void matrizDynamicFree(int N,double **A,double **B,double **C);
void initMatriz(int N,double *A,double *B,double *C);
void initTranspose(int N,double *B,double *T);
void impresion(int N, double *matriz);
void multiplyMatrix(int MATRIX_SIZE, double **matrixA, double **matrixB, double **result);
#endif
