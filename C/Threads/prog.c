//000148441
/*
 ============================================================================
 Name        : yes.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <pthread.h>
#include <string.h>

typedef struct{
	char nombre[21];
	char ocupacion[21];
	int edad;
}Persona;

typedef struct{
	int count;
	Persona* personas;
	char file[64];
}Params;

void* imprimirEstructuraInverso(void* args){
	Params *params = (Params *)args;

	int cont;
	cont = params -> count;

	Persona *personas = params -> personas;

	FILE *OUT_FILE = fopen(params -> file, "w");

	for(int i = cont - 1; i >= 0; i--){
			fprintf(OUT_FILE, "%s %s %d\n",personas[i].nombre, personas[i].ocupacion, personas[i].edad);
	}

	fclose(OUT_FILE);
	return NULL;
}

void* imprimirOrdenAlfabetico(void* args){
	Params *params = (Params *)args;

	int cont;
	cont = params -> count;

	Persona *personas = params -> personas;

	//Organizo los registros en un arreglo primero
	Persona persones[cont];

	for(int i = 0; i < cont; i++){
		persones[i] = *(personas + i);
	}
	puts("");
	//Sort
	Persona temp;
	for(int i = 0; i < cont; i++){
		for(int j = 0; j < cont ; j++){
			if(strcmp(persones[i].ocupacion, persones[j].ocupacion) < 0){
				temp = persones[i];
				persones[i] = persones[j];
				persones[j] = temp;
			}
		}
	}

	FILE *OUT_FILE = fopen(params -> file, "w");

	for(int i = 0; i < cont; i++){
		fprintf(OUT_FILE, "%s %s %d\n",persones[i].nombre, persones[i].ocupacion, persones[i].edad);
	}

	fclose(OUT_FILE);
	return NULL;
}

 int main(int argc, char *argv[])
{
	pthread_t id_hilo1;
	pthread_t id_hilo2;
	Persona personas[100];

	//Leer archivo y guardar información en estructuras
	FILE *file = fopen(argv[1],"r");

	char buffer[21];

	if(file == NULL){
		perror("No se pudo abrir el arhivo");
	}

	int cont = 0;
	while(fgets(buffer,20,file) != NULL){

		sscanf(buffer, "%20s %20s %d", personas[cont].nombre, personas[cont].ocupacion, &personas[cont].edad);
		cont++;
	}


	//Imprimir información organizada en estructuras
	for(int i = 0; i < cont; i++){
		printf("%s %s %d\n",personas[i].nombre, personas[i].ocupacion, personas[i].edad);
	}


	//Parametros Hilo 1
	Params *args1 = malloc(sizeof(Params) * cont);
	args1 -> count = cont;
	args1 -> personas = &personas[0];
	strcpy(args1 -> file, argv[2]);

	//Parametros Hilo 2
	Params *args2 = malloc(sizeof(Params) * cont);
	args2 -> count = cont;
	args2 -> personas = &personas[0];
	strcpy(args2 -> file, argv[3]);

	pthread_create(&id_hilo1, NULL, &imprimirEstructuraInverso, (void *)args1);
	pthread_create(&id_hilo2, NULL, &imprimirOrdenAlfabetico, (void *)args2);


	pthread_join(id_hilo1, NULL);
	pthread_join(id_hilo2, NULL);

	//Imprimir resultados

	puts("Hilos Terminados");
	puts("Archivo de Salida 1 (Registros en orden inverso)");

	FILE* OUT_FILE1 = fopen(argv[2], "r");

	while(fgets(buffer, 20, OUT_FILE1) != NULL){
		printf("%s", buffer);
	}

	fclose(OUT_FILE1);

	puts("Archivo de Salida 2 (Registros en Alfabético)");

		FILE* OUT_FILE2 = fopen(argv[3], "r");

		while(fgets(buffer, 20, OUT_FILE2) != NULL){
			printf("%s", buffer);
		}

		fclose(OUT_FILE2);

	return 0;
}
