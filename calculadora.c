/*
 ============================================================================
 Name        : calculadora.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void printArray(float arr[]);
void fillArray(float *arr[]);
void calcProm(float* prom, float arr[]);

int main(void) {
	float array[100];
	float prom = 0.0f;

	fillArray(&array);
	printArray(array);
	calcProm(&prom, array);
	printf("%0.2f", prom);
	return EXIT_SUCCESS;
}

void printArray(float arr[]){
	for(int i = 0; i < 100; i++){
		printf("|%1.0f", arr[i]);
	}

	puts("\n");
}

void fillArray(float *arr[]){
	float* ptr = arr;

	for(int i = 0; i < 100; ptr++){
		*ptr = i;
		i++;
	}
}

void calcProm(float* prom, float arr[]){
	for(int i = 0; i < 100; i++){
		*prom += arr[i];
	}

	*prom /= 100;
}
