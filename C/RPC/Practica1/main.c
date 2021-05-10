#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Client needs
void genArrays(int *values, int numValues, int *array1, int *array2, int array1len, int array2len);
void *readFile(char *path, char *host, int *numvals, int *arr1len, int *arr2len);
void *readArgs(int argc, char *argv[], int *arr1len, int *arr2len);
int mayorValor(int *arr, int size);

//Server needs
int isPerfect(int n);
int maxNoPerfect(int *arr, int size);
int minOdd(int *arr, int size);
int productoPunto(int *arr1, int *arr2, int size);
double medioRangoEspecial(int minOdd, int maxNoPerfect);

int main(int argc, char *argv[])
{

    int *valores;
    int numVals;
    char host[20];
    int array1[50];
    int array2[50];
    int arr1len;
    int arr2len;
    int productoP;
    double medioRangoE;

    if (argc == 2)
    {
        valores = (int *)readFile(argv[1], host, &numVals, &arr1len, &arr2len);
    }
    else if (argc > 2)
    {
        //host siempre es argv[1]
        strcpy(host, argv[1]);
        valores = (int *)readArgs(argc, argv, &arr1len, &arr2len);
        numVals = atoi(argv[2]);
    }
    else
    {
        printf("Cantidad de argumentos inválida\n");
        exit(1);
    }
    printf("Calling RPC on %s\n", host);

    genArrays(valores, numVals, array1, array2, arr1len, arr2len);
    free(valores);

    int mayorVec1 = mayorValor(array1, arr1len);
    int mayorVec2 = mayorValor(array2, arr2len);

    if (mayorVec1 >= mayorVec2)
    {
        productoP = productoPunto(array1, array2, arr1len);
        printf("Producto Punto: %d\n", productoP);
    }
    else
    {
        medioRangoE = medioRangoEspecial(minOdd(array1, arr1len), maxNoPerfect(array2, arr2len));
        printf("Medio Rango Especial: %f\n", medioRangoE);
    }

    return 0;
}

void *readFile(char *path, char *host, int *numvals, int *arr1len, int *arr2len)
{

    char buffer[150];
    char values_raw[101];
    int num_elems;

    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        printf("Cannot open %s\n", path);
        exit(8);
    }
    //Leer hasta el fin o hasta que se rompa
    fgets(buffer, 50, file);
    if (sscanf(buffer, "%s %d %[^\t\n]", host, &num_elems, values_raw) != 3)
    {
        perror("El archivo tiene un formato incorrecto\n");
        exit(4);
    }

    fclose(file);
    int *valores = (int *)malloc(sizeof(int) * num_elems);
    *numvals = num_elems;
    char *token = strtok(values_raw, " ");

    for (int i = 0; token != NULL; i++)
    {
        valores[i] = atoi(token);
        token = strtok(NULL, " ");
    }

    *arr1len = num_elems / 2;
    *arr2len = *arr1len;

    return valores;
}

void *readArgs(int argc, char *argv[], int *arr1len, int *arr2len)
{

    //Número de argumentos a leer es siempre es argv[2]
    int num_elems = atoi(argv[2]);
    int *valores = (int *)malloc(sizeof(int) * num_elems);

    for (int i = 0; i < num_elems; i++)
    {
        valores[i] = atoi(argv[3 + i]);
    }

    *arr1len = num_elems / 2;
    *arr2len = *arr1len;

    return valores;
}

void genArrays(int *values, int numValues, int *array1, int *array2, int array1len, int array2len)
{
    if (numValues % 2 == 1)
    {
        //Es impar, ignorar elemento de la mitad
        for (int i = 0; i < array1len; i++)
        {
            array1[i] = values[i];
            array2[i] = values[i + array1len + 1];
        }
    }
    else
    {
        for (int i = 0; i < array1len; i++)
        {
            array1[i] = values[i];
            array2[i] = values[i + array1len];
        }
    }
}

int mayorValor(int *arr, int size)
{
    int max = arr[0];
    for (int i = 0; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    return max;
}

int productoPunto(int *arr1, int *arr2, int size)
{
    int productoPunto = 0;

    for (int i = 0; i < size; i++)
    {
        productoPunto += arr1[i] * arr2[i];
    }

    return productoPunto;
}

int minOdd(int *arr, int size)
{

    int foundOdd = 0;
    int min = arr[0];

    for (int i = 0; i < size; i++)
    {
        if ((arr[i] % 2 == 1 || arr[i] % 2 == -1) && arr[i] <= min)
        {
            foundOdd = 1;
            min = arr[i];
        }
    }

    if (foundOdd)
    {
        return min;
    }

    return 0;
}

int maxNoPerfect(int *arr, int size)
{
    int max = arr[0];
    int foundNoPerfect = 0;

    for (int i = 0; i < size; i++)
    {
        if (!isPerfect(arr[i]) && arr[i] > max)
        {
            max = arr[i];
            foundNoPerfect = 1;
        }
    }

    if (foundNoPerfect)
    {
        return max;
    }

    return 0;
}

int isPerfect(int n)
{
    int sum = 0;
    for (int i = 1; i < n; i++)
    {
        if (n % i == 0)
        {
            sum += i; //Sumar divisor
        }
    }

    if (sum == n)
    {
        return 1;
    }
    return 0;
}

double medioRangoEspecial(int minOdd, int maxNoPerfect)
{
    return (minOdd + maxNoPerfect) / 2.0;
}

//test
// ./main 127.0.0.1 7 2 3 4 5 3 1 2
// Producto punto 17

//test2
// ./main localhost 7 1 -3 -4 12 -3 28 2
// Medio Rango Especial 0.5
