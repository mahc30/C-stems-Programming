#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define LENGTH_ODD_ARRAY(x) (x)
#define LENGTH_EVEN_ARRAY(x) (x - 1)

void printIntArray(int *array, int size);
void printStringArray(char *array[], int size);
void genArraysEven(int *values, int* array1, int* array2, int size);
void genArraysOdd(int *values, int* array1, int* array2, int size);
void *readFile(char *path, char* host, int *arraySize);
void *readArgs(int argc, char *argv[], int *arraySize);
int productoPunto(int *arr1, int *arr2, int size);
double medioRangoEspecial(int minOdd, int maxPrime);
int esPrimo(int n);
int maxPrime(int *arr, int size);
int minOdd(int *arr, int size);
int productoPunto(int *arr1, int *arr2, int size);

int main(int argc, char *argv[]) {

    int arraySize;
    char host[20];
    int *valores;
    int productoP;
    double medioRangoE;

    if(argc == 2)
    {
        valores = (int *)readFile(argv[1], host, &arraySize);
    }
    else if(argc > 2)
    {
        //host siempre es argv[1]
        strcpy(host, argv[1]);
       valores = (int *)readArgs(argc, argv, &arraySize);
    }
    else
    {
        printf("Cantidad de argumentos inválida");
    }

    //El tamaño de los arreglos es argv[2]/2 redondeado hacia arriba
    int isEven = arraySize % 2;
    arraySize = (int)ceil((double)arraySize / 2);
    int *array1;
    int *array2;

    switch (isEven)
    {
    case 0:
        //Par
        array1 = (int *)malloc(sizeof(int) * arraySize);
        array2 = (int *)malloc(sizeof(int) * arraySize);

        genArraysEven(valores, array1, array2, arraySize);

        productoP = productoPunto(array1, array2, arraySize);
        medioRangoE = medioRangoEspecial(minOdd(array1, arraySize), maxPrime(array2, arraySize));
        break;
    case 1:
        //Impar
        array1 = (int *)malloc(sizeof(int) * LENGTH_EVEN_ARRAY(arraySize));
        array2 = (int *)malloc(sizeof(int) * (arraySize + 1));

        genArraysOdd(valores, array1, array2, arraySize);

        productoP = productoPunto(array1, array2, LENGTH_EVEN_ARRAY(arraySize));
        medioRangoE = medioRangoEspecial(minOdd(array1, LENGTH_EVEN_ARRAY(arraySize)), maxPrime(array2, arraySize));

    break;
    default:
        printf("Error generando los arrays ¿¿¿¿\n");
        break;
    }       

    printf("Producto Punto: %d\nMedio Rango Especial: %f\n", productoP, medioRangoE);
    return 0;
}

void printIntArray(int *array, int size){
    for(int i = 0; i < size; i++){
        printf("valores[%d] = %d\n", i, array[i]);
        
    }
}

void printStringArray(char *array[], int size){
     for(int i = 0; i < size; i++){
        printf("args[%d] = %s\n", i, array[i]);
    }
}

void genArraysEven(int *values, int* array1, int* array2, int size){
    for(int i = 0; i < size; i++){
        array1[i] = values[i];
        array2[i] = values[i + size];
    }
}

void genArraysOdd(int *values, int* array1, int* array2, int size){
    for(int i = 0; i < size - 1; i++){
        array1[i] = values[i];
        array2[i] = values[i + size - 1];
    }

    array2[size - 1] = values[size* 2 - 2];
}


void *readFile(char *path, char* host, int *arraySize){

    char buffer[50];
    char values_raw[30];
    char host_raw[20];

    FILE *file = fopen(path, "r");

    if(file == NULL){
			printf("Cannot open %s\n", path);
			exit(8);
	}
	//Leer hasta el fin o hasta que se rompa
    fgets(buffer, 50, file);
	if(sscanf(buffer, "%s %d %[^\t\n]", host_raw, arraySize, values_raw) != 3){
        perror("No se pudo leer el archivo\n");
	}

	fclose(file);

    int *valores = (int *)malloc(sizeof(int) * (*arraySize));
    
    char *token = strtok(values_raw, " ");
    for(int i = 0 ; token != NULL; i++){
        valores[i] = atoi(token);
        printf("Token %s Valores[%d] : %d\n", token, i, valores[i]);
        token = strtok(NULL, " ");
    }

    return valores;
}

void *readArgs(int argc, char *argv[], int *arraySize){

    //Número de argumentos a leer es argv[2] redondeado hacia arriba
    *arraySize = atoi(argv[2]);
    if(*arraySize < 0){
        printf("El tamaño de los arreglos debe ser mayor a 0");
    }
    
    if(argc + 3 < *arraySize){
        printf("La cantidad de valores no concuerda con el tamaño del arreglo");
    }

    int *valores = (int *)malloc(sizeof(int) * (*arraySize));
    
    for(int i = 0 ; i < *arraySize; i++){
        valores[i] = atoi(argv[3 + i]);
    }

    return valores;
}

int productoPunto(int *arr1, int *arr2, int size){
    int productoPunto = 0;

    for(int i = 0; i < size; i++){
        productoPunto += arr1[i] * arr2[i];
    }

    return productoPunto;
}

int minOdd(int *arr, int size){

    int foundOdd = 0;
    int min = arr[0];

    for(int i = 0; i < size; i++){
        if(arr[i] % 2 == 1 && arr[i] <= min){
            foundOdd = 1;
            min = arr[i];
        }
    }

    if(foundOdd){
        return min;
    }

    return 0;
}

int maxPrime(int *arr, int size){
    int max = 0;
    for(int i = 0; i < size; i++){
        if(esPrimo(arr[i]) && arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

int esPrimo(int n){
    for(int i = 0; i < n; i++){
        for(int j = 2; j <= i; j++){
            if(n % j == 0){
                return 0; //No es Primo
            }
        }
    }
    return 1;
}

double medioRangoEspecial(int minOdd, int maxPrime){
    printf("minOdd: %d maxPrime: %d MedioRango: %f\n", minOdd, maxPrime, (minOdd + maxPrime) / 2.0);
    return (minOdd + maxPrime) / 2.0;
}

//test
// ./main 127.0.0.1 6 2 6 4 3 1 2
// Producto punto 20
// Medio rango especial 1.5
// longitud de los vectores 3 (6/2)
