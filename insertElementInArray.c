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

/*
 * Se propone realizar un programa que:

    Solicite el tamaño de un arreglo.
    Solicite uno por uno sus elementos.
    Realice una función para imprimir el contenido del arreglo. A esta función deberá pasar la dirección del arreglo y el tamaño.
    Permita insertar un nuevo elemento en el arreglo mediante la selección de la posición deseada en el arreglo que irá desde 1 hasta el tamaño del arreglo.
 *
 */

void llenarArreglo(int size, int *array);
void imprimirArreglo(int size, int *array);
void insertarElemento(int size,int *array,int element,int pos);

int main(void) {
	int size;
	int element;
	int pos;

	puts("\nTamaño del Arreglo: ");
	scanf("%d", &size);

	int array[size + 1];
	llenarArreglo(size, &(array[0]));
	imprimirArreglo(size, &(array[0]));

	puts("\nElemento: ");
	scanf("%d", &element);

	puts("\nPosición: ");
	scanf("%d", &pos);

	insertarElemento(size, array, element, pos);
	size++;
	imprimirArreglo(size, &(array[0]));

	return(0);
}

void llenarArreglo(int size, int *array){

	int ins;
	for(int i = 0; i < size; i++){
		printf("Insertar elemento %d:\n", i + 1);
		scanf("%d", &ins);
		*(array + i) = ins;
	}
}

void imprimirArreglo(int size, int *array){
	for(int i = 0; i < size; i++){
		printf("|%d", *(array + i));
	}
}

void insertarElemento(int size,int *array,int element,int pos){
	for(int i = size; i > pos; i--){
		*(array + i) = *array + i - 1;
	}

	*(array + pos) = element;
}

