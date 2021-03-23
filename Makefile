 #
 #              Archivo: Makefile
 #				Universidad Sergio Arboleda
 #      		Escuela de ingenieria y ciencias exactas
 #      		Programas: Ingenieria de sistemas y telecomunicaciones
 #                 		   Ingenieria electrónica
 #              Autor: Nicolas Cifuentes Barriga <nicolas.cifuentes01@correo.usa.edu.co>
 #					   Santiago Gutierrez Orjuela <santiago.gutierrez02@correo.usa.edu.co>
 #					   Daniel Siachoque Peralta <daniel.siachoque01@correo.usa.edu.co>
 #					   Guillermo Torres Delgado <juan.torres01@correo.usa.edu.co>
 #              Ultima modificación: Marzo 13, 2021
 #              Sesión: Multiplicación de matrices clásica y transpuesta
 #-----------------------------------------------------------------------------------------------
 #
 #      RESUMEN:
 #      =======
 #      Este archivo facilita la automatización y optimización para el proceso de compilación
 #		de cada uno de los ficheros componentes de la aplicación (mClasica.c, mTranspuesta.c, 
 #		interfaz.h y modulo.c) resumiendo su comportamiento en los siguientes comandos:
 #      - make all: inicia la compilación y enlace entre ficheros
 #		- make clean: elimina de la carpeta los archivos y ejecutable creados por el comando previo
 #

#Variable de entorno para el comando gcc
GCC = gcc -fopenmp
#Variable de entorno para las banderas requeridas durante la compilación
FLAGS = -ansi -pedantic -Wall -std=c99
#Variable de entorno para banderas opcionales
CFLAGS = -l
#variable de entorno para referirse a las palabras mClasica y mTranspuesta
PROGS = MM1c MM1t MM1cDynamic

#Función tomada en cuenta para toda la ejecución
all: $(PROGS)

#Función que realiza los comandos que contenga
MM1c:
#Comando para compilar  modelo.c usando las variables de entorno correspondientes
	$(GCC) $(FLAGS) modulo.c -c
#Comando para compilar  principal.c usando las variables de entorno correspondientes
	$(GCC) $(FLAGS) $@.c -c
#Comando para fusionar con el ejecutable los objetos resultantes de las compilaciones previas
	$(GCC) $(FLAGS) -o $@ $@.o modulo.o

MM1t:
#Comando para compilar  modelo.c usando las variables de entorno correspondientes
	$(GCC) $(FLAGS) modulo.c -c
#Comando para compilar  principal.c usando las variables de entorno correspondientes
	$(GCC) $(FLAGS) $@.c -c
#Comando para fusionar con el ejecutable los objetos resultantes de las compilaciones previas
	$(GCC) $(FLAGS) -o $@ $@.o modulo.o

MM1cDynamic:
#Comando para compilar  modelo.c usando las variables de entorno correspondientes
	$(GCC) $(FLAGS) modulo.c -c
#Comando para compilar  principal.c usando las variables de entorno correspondientes
	$(GCC) $(FLAGS) $@.c -c
#Comando para fusionar con el ejecutable los objetos resultantes de las compilaciones previas
	$(GCC) $(FLAGS) -o $@ $@.o modulo.o

#Función que realiza los comandos que contenga
clean:
#Elimina todo objeto .o en la carpeta
	$(RM) $(PROGS) *.o
#Elimina todo archivo con el nombre de la variable de entorno correspondiente (en este caso el ejecutable)
	$(RM) $(PROGS) $
