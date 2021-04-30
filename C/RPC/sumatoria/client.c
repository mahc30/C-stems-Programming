#include "productoPunto.h"
#include <math.h>

#ifndef _CLIENTAUX
#define _CLIENTAUX
void genArrays(int *values, int *array1, int *array2, int arr1len, int arr2len);
void *readFile(char *path, char *host, int *arr1len, int *arr2len);
void *readArgs(int argc, char *argv[], int *arr1len, int *arr2len);

void genArrays(int *values, int *array1, int *array2, int array1len, int array2len)
{
    for (int i = 0; i < array1len; i++)
    {
        array1[i] = values[i];
        array2[i] = values[i + array1len];
    }

    if (array1len < array2len)
    {
        //Es impar, agregar último elemento al arreglo 2
        array2[array2len - 1] = values[array2len * 2 - 2];
    }
}

void *readFile(char *path, char *host, int *arr1len, int *arr2len)
{

    char buffer[50];
    char values_raw[30];
    char host_raw[20];
    int num_elems;

    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        printf("Cannot open %s\n", path);
        exit(8);
    }
    //Leer hasta el fin o hasta que se rompa
    fgets(buffer, 50, file);
    if (sscanf(buffer, "%s %d %[^\t\n]", host_raw, &num_elems, values_raw) != 3)
    {
        perror("El archivo tiene un formato incorrecto\n");
        exit(4);
    }

    fclose(file);

    int *valores = (int *)malloc(sizeof(int) * num_elems);
    char *token = strtok(values_raw, " ");

    for (int i = 0; token != NULL; i++)
    {
        valores[i] = atoi(token);
        token = strtok(NULL, " ");
    }

    int isOdd = num_elems % 2;

    if (isOdd)
    {
        //impar
        *arr2len = (int)ceil((double)num_elems / 2);
        *arr1len = *arr2len - 1;
    }
    else
    {
        //par
        *arr1len = num_elems / 2;
        *arr2len = *arr1len;
    }

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

    int isOdd = num_elems % 2;

    if (isOdd)
    {
        //impar
        *arr2len = (int)ceil((double)num_elems / 2);
        *arr1len = *arr2len - 1;
    }
    else
    {
        //par
        *arr1len = num_elems / 2;
        *arr2len = *arr1len;
    }

    return valores;
}

#endif

void prog_op_1(char *host)
{
    CLIENT *clnt;
    int *result_1;
    vectores productopunto_1_arg;
    double *result_2;
    vectores mediorangoespecial_1_arg;

    productopunto_1_arg.array1[0] = 1;
    productopunto_1_arg.array1[1] = 2;
    productopunto_1_arg.array1[2] = 3;
    productopunto_1_arg.array2[0] = 4;
    productopunto_1_arg.array2[1] = 5;
    productopunto_1_arg.array2[2] = 6;
    productopunto_1_arg.arr1len = 3;
    productopunto_1_arg.arr2len = 3;

    mediorangoespecial_1_arg.array1[0] = 1;
    mediorangoespecial_1_arg.array1[1] = 2;
    mediorangoespecial_1_arg.array1[2] = 3;
    mediorangoespecial_1_arg.array2[0] = 4;
    mediorangoespecial_1_arg.array2[1] = 5;
    mediorangoespecial_1_arg.array2[2] = 6;
    mediorangoespecial_1_arg.arr1len = 3;
    mediorangoespecial_1_arg.arr2len = 3;

#ifndef DEBUG
    clnt = clnt_create(host, PROG_OP, VERS_OP, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror(host);
        exit(1);
    }
#endif /* DEBUG */

    result_1 = productopunto_1(&productopunto_1_arg, clnt);
    if (result_1 == (int *)NULL)
    {
        clnt_perror(clnt, "call failed");
    }
    result_2 = mediorangoespecial_1(&mediorangoespecial_1_arg, clnt);
    if (result_2 == (double *)NULL)
    {
        clnt_perror(clnt, "call failed");
    }

#ifndef DEBUG
    clnt_destroy(clnt);
#endif /* DEBUG */

    printf("Producto Punto: %d\nMedio Rango Especial: %0.3f\n", *result_1, *result_2);
}

int main(int argc, char *argv[])
{
    char *host;

    if (argc < 2)
    {
        printf("usage: %s server_host\n", argv[0]);
        exit(1);
    }
    host = argv[1];
    prog_op_1(host);
    exit(0);
}
