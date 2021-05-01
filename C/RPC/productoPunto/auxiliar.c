#include <stdlib.h>
#include <stdio.h>

void genArrays(int *values, int* array1, int* array2, int array1len, int array2len){
    for(int i = 0; i < array1len; i++){
        array1[i] = values[i];
        array2[i] = values[i + array1len];
    }

    if(array1len < array2len){
        //Es impar, agregar último elemento al arreglo 2
        array2[array2len - 1] = values[array2len * 2 - 2];
    }
}

void *readFile(char *path, char* host, int *arr1len, int *arr2len){

    char buffer[50];
    char values_raw[30];
    char host_raw[20];
    int num_elems;

    FILE *file = fopen(path, "r");

    if(file == NULL){
			printf("Cannot open %s\n", path);
			exit(8);
	}
	//Leer hasta el fin o hasta que se rompa
    fgets(buffer, 50, file);
	if(sscanf(buffer, "%s %d %[^\t\n]", host_raw, &num_elems, values_raw) != 3){
        perror("El archivo tiene un formato incorrecto\n");
        exit(4);
	}

	fclose(file);

    int *valores = (int *)malloc(sizeof(int) * num_elems);
    char *token = strtok(values_raw, " ");

    for(int i = 0 ; token != NULL; i++){
        valores[i] = atoi(token);
        token = strtok(NULL, " ");
    }

    int isOdd = num_elems % 2;

    if(isOdd){
        //impar
        *arr2len = (int)ceil((double)num_elems / 2);
        *arr1len = *arr2len - 1;
    }
    else{
        //par
        *arr1len = num_elems / 2;
        *arr2len = *arr1len;
    }

    return valores;
}

void *readArgs(int argc, char *argv[], int *arr1len, int *arr2len){

    //Número de argumentos a leer es siempre es argv[2]
    int num_elems = atoi(argv[2]);
    int *valores = (int *)malloc(sizeof(int) * num_elems);
    
    for(int i = 0 ; i < num_elems; i++){
        valores[i] = atoi(argv[3 + i]);
    }

    int isOdd = num_elems % 2;

    if(isOdd){
        //impar
        *arr2len = (int)ceil((double)num_elems / 2);
        *arr1len = *arr2len - 1;
    }
    else{
        //par
        *arr1len = num_elems / 2;
        *arr2len = *arr1len;
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
    return (minOdd + maxPrime) / 2.0;
}