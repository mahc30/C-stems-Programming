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
const char FILE_PATH[] ="./files/original.txt";
float calcularPromedio(int size, float notas[], int creditos[]);
void tabla(int size, char *materias, float notas[], int creditos[], float promedio);

int main(void) {

	//Leer archivo origen

	float promedio;
	//Abrir Archivo
	FILE *in_file = fopen(FILE_PATH, "r");
	if(in_file == NULL){
		printf("Cannot open %s\n", FILE_PATH);
		exit(8);
	}

	char string[32];
	char materia[15][64];
	float nota[32];
	int creditos[32];
	int cant_materias = 0;
	//Leer hasta el fin o hasta que se rompa
	while(fscanf(in_file, "%s %s", string, materia + cant_materias) == 2){

		fscanf(in_file, "%s %f", string, nota + cant_materias);
		fscanf(in_file, "%s %d", string, creditos + cant_materias);

		cant_materias++;
	}
	printf("\nNumber of Lines in %s is %d\n", FILE_PATH, cant_materias);
	fclose(in_file);
/*
	for(int i = 0; i < cant_materias; i++){
		printf("\n%s",materia[0] + i);
		printf("\n%.2f", *(nota + i));
		printf("\n%d", *(creditos + i));
	}

*/
	promedio = calcularPromedio(cant_materias, nota, creditos);

	tabla(cant_materias, materia, nota, creditos, promedio);

	return(0);
}


float calcularPromedio(int size, float notas[], int creditos[]){
	int total_creditos = 0;
	float ponderado = 0;
	float promedio;

	for(int i = 0; i < size; i++){
		ponderado += (float)(notas[i] * (float)creditos[i]);
	}

	for(int i = 0; i < size; i++){
		total_creditos += creditos[i];
	}

	promedio = ponderado / total_creditos;
	return promedio;
}

void tabla(int size, char materias[], float notas[], int creditos[], float promedio){


	//Crear Archivo
		char *newFilePath = "./files/nuevo.txt";

		FILE *newFile = fopen(newFilePath, "w");


	fprintf(newFile, "\n 		Materia   				|Nota			|Créditos\n");
	char (*ptr)[64] = materias;
	int materias_ganadas = 0;
	int materias_perdidas;

	for(int i = 0; i < size; i++){
		fprintf(newFile, "%-20s\t\t\t|%.2f\t\t\t|%d\n", *(ptr + i), notas[i], creditos[i]);

		if(notas[i] > 3.5){
			materias_ganadas++;
		}
	}

	materias_perdidas = size - materias_ganadas;

	fprintf(newFile, "\nTotal de Materias: %d\nMaterias Ganadas: %d\nMaterias Perdidas: %d\nPromedio Ponderado: %.2f", size, materias_ganadas, materias_perdidas, promedio);
	fclose(newFile);

}
