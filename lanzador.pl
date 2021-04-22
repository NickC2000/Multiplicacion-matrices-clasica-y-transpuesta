#!/usr/bin/perl   
#En Perl, el encabezado debe ir siempre de esa forma
#el encabezado /usr/bin/perl ubicar el compilador e interprete de PERL

######################
# Fecha: 16_02_2021
# Asignatura: Computación Paralela y Distribuida 
# Ciencias de la Computación
# Asunto: Programa que permite hacer lanzamiento automático de una Bateria de Experimentos
#
######################

if(@ARGV[0])
	{
		$InFile = "$ARGV[0]";
	}
else
	{
		usage();
	}


$path0 = `pwd`;
chomp($path0);
$T = index($path0,"T")-1;
#$Path = substr($path0,0,$T);
$Path = $path0;

$N = 1;  # Número de Repeticiones
@Ejecutable = ("MM1c","MM1f","MM1fDynamic","MM2f","multiplicacion_pthread"); # nombre de los ejecutables (benchmarks)
@cores = ("1","2","4","8"); # Número de hilos de ejecución
@MatrizSize = ("600", "1000", "2000", "4000", "6000");   ### Dimensión de la matriz para Pthread 


foreach $size (@MatrizSize){
foreach $exe (@Ejecutable){
    foreach $c (@cores) {
        $file = "$Path/"."Soluciones/"."$exe"."-Size"."$size"."-cores-"."$c";
        #print "$file \n";
        for($i=0; $i<$N;  $i++){
	       	system("$Path/$exe $size $c >> $file");
            print "$Path/$exe $size $c \n" ;
        }
    close($file);
    }
}
}


	exit(1);

sub usage()
{
	print "\n tst.pl: Error incorrect usage \n\n";
	print "\t <directory> Is directory start point to check \n\n\n";
	exit(1);
}
