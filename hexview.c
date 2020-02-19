//000148441
/*
 ============================================================================
 Name        : hexview.c
 Author      : Miguel Ángel Hincapié Calle ID: 000148441
 Version     :
 Copyright   : Your copyright notice
 Description : Primer Parcial
 ============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int main(int argc, char *argv[]) {

	char *arg1 = argv[1];
	char *arg2 = argv[2];

	//Creo la ruta del archivo 1
	char path1[sizeof(arg1)] = "./";
	strcat(path1,arg1);

	//Creo la ruta del archivo 2
	char path2[sizeof(arg2)] = "./";
	strcat(path2,arg2);

	//Abrir archivo de entrada
	FILE *in = fopen(path1, "r");
	//Archivo de salida
	FILE *out = fopen(path2, "w");
	if(in == NULL){
			printf("Cannot open %s\n", path1);
			exit(8);
	}

	int ch;
	int count = 0;
		//Leer hasta el fin o hasta que se rompa
	while(1){
		ch = fgetc(in);
		if(ch == EOF){
			break;
		}

		/*Funciona, hace lo que quiero, pero me da miedo porque solo tengo este caso de prueba :( */
		fprintf(out, "%.2hhX ", ch);

		count++;
	}

		//Comprobar si llegó a fin del archivo o error
	if (!feof(in)){
		printf("\n Error Leyendo el Archivo.");
	}

	fclose(in);
	fclose(out);
	return(0);
}

