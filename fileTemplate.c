/*
 ============================================================================
 Name        : sistemasOperativos.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
const char FILE_NAME[] ="./files/original.txt";


int main(void) {

	char data[1000];
	char* in = data;
	//Leer archivo origen
	int count = 0;
	FILE *in_file;

	//Abrir Archivo
	int ch;
	in_file = fopen(FILE_NAME, "r");
	if(in_file == NULL){
		printf("Cannot open %s\n", FILE_NAME);
		exit(8);
	}

	//Leer hasta el fin o hasta que se rompa
	while(1){
		ch = fgetc(in_file);
		*(in + count) = ch;
		if(ch == EOF){
			break;
		}else{
			count++;
		}
	}

	//Comprobar si llegó a fin del archivo o error
	if (feof(in_file)){
	     printf("\n End of file reached.");
		 data[count] = 0;
	}
	  else printf("\n Something went wrong.");

	printf("\nNumber of characters in %s is %d\n", FILE_NAME, count);
	fclose(in_file);


	printf("\n%s",data);

	//Crear Archivo
	char *newFilePath = "./files/nuevo.txt";

	FILE *newFile = fopen(newFilePath, "w");
	fputs(data, newFile);

	return(0);
}
