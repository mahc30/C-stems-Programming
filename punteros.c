/*
 ============================================================================
 Name        : punteros.c
 Author      : mahc30
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/*
 *
 * Realice un programa que permita calcular
el promedio ponderado obtenido por un
estudiante en el semestre, considerando:
1.El programa debe solicitar el número de
materias vistas en el semestre.
2.Debe preguntar el nombre de la materia.
3.Debe preguntar la nota obtenida.
4.Debe solicitar el número de créditos.
5.Al final, debe mostrar una tabla con
tantas filas como materias y con 3
columnas indicando el nombre de la
materia, la nota y el número de créditos.
6.También debe reportar el promedio
ponderado.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void llenarMaterias(int cant_m, char (*nombres)[14], int notas[], int creditos[]);
void printStringArray(char arr[]);
void printIntArray(int size, int arr[]);
void printFloatArray(int size, float arr[]);
float calcularPromedio(int size, float notas[], int creditos[]);

int main(void) {

	int cant_materias;


	puts("Ingrese el número de materias: \n");
	scanf("%d", &cant_materias);

	//Ya que tengo la cantidad de materias puedo crear los arreglos
	char nombre_materias[cant_materias][14];
	float nota_materias[cant_materias], promedio;
	int cant_creditos[cant_materias];

	//Lleno los arreglos
	llenarMaterias(cant_materias, nombre_materias, nota_materias, cant_creditos);

	//Obtengo promedio
	promedio = calcularPromedio(cant_materias, nota_materias, cant_creditos);

	//Imprimir
	puts("Materias ");
	for(int i = 0; i < cant_materias; i ++){
			printStringArray(nombre_materias + i);
	}
	puts("\n");
	puts("notas    ");
	printFloatArray(cant_materias, nota_materias);
	puts("\n");
	puts("creditos ");
	printIntArray(cant_materias, cant_creditos);
	puts("\n");
	printf("Promedio: %2.2f", promedio);

	return EXIT_SUCCESS;
}

void llenarMaterias(int cant_m, char (*nombres)[14],  int notas[], int creditos[]){


	for(int i = 0; i < cant_m; i++){
		printf("Escriba el nombre de la %d materia: \n", i+1);
		scanf("%s", nombres + i);

		puts("Escriba la nota: \n");
		scanf("%f", notas + i);

		puts("Escriba la cantidad de creditos: \n");
		scanf("%d", creditos + i);
	}
}

void printStringArray(char arr[]){
	printf("%s  |", arr);
}

void printIntArray(int size, int arr[]){
	for(int i = 0; i < size; i++){
		printf("%d   |", arr[i]);
	}
}

void printFloatArray(int size, float arr[]){
	for(int i = 0; i < size; i++){
		printf("%.2f |", arr[i]);
	}
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
