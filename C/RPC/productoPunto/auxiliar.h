#ifndef _AUXILIAR_H
#define _AUXILIAR_H

//Client needs
void genArrays(int *values, int* array1, int* array2, int arr1len, int arr2len);
void *readFile(char *path, char* host, int *arr1len, int *arr2len);
void *readArgs(int argc, char *argv[], int *arr1len, int *arr2len);

//Server needs
int esPrimo(int n);
int maxPrime(int *arr, int size);
int minOdd(int *arr, int size);
int productoPunto(int *arr1, int *arr2, int size);
double medioRangoEspecial(int minOdd, int maxPrime);

#endif