#include "productoPunto.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef _SERVERAUX
#define _SERVERAUX
int esPrimo(int n);
int maxPrime(int *arr, int size);
int minOdd(int *arr, int size);
int productoPunto(int *arr1, int *arr2, int size);
double medioRangoEspecial(int minOdd, int maxPrime);

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
        if (arr[i] % 2 == 1 && arr[i] <= min)
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

int maxPrime(int *arr, int size)
{
    int max = 0;
    for (int i = 0; i < size; i++)
    {
        if (esPrimo(arr[i]) && arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int esPrimo(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 2; j <= i; j++)
        {
            if (n % j == 0)
            {
                return 0; //No es Primo
            }
        }
    }
    return 1;
}

double medioRangoEspecial(int minOdd, int maxPrime)
{
    return (minOdd + maxPrime) / 2.0;
}

#endif

int *productopunto_1_svc(vectores *argp, struct svc_req *rqstp)
{
    static int result;

    int *array1 = argp->array1;
    int *array2 = argp->array2;
    int arr1len = argp->arr1len;

    //Par
    result = productoPunto(array1, array2, arr1len);

    return &result;
}

double *
mediorangoespecial_1_svc(vectores *argp, struct svc_req *rqstp)
{
    static double result;

    int *array1 = argp->array1;
    int *array2 = argp->array2;
    int arr1len = argp->arr1len;
    int arr2len = argp->arr2len;

    if (arr1len == arr2len)
    {
        //Par
        result = medioRangoEspecial(minOdd(array1, arr1len), maxPrime(array2, arr2len));
    }
    else
    {
        //impar
        result = medioRangoEspecial(minOdd(array1, arr1len), maxPrime(array2, arr2len));
    }

    return &result;
}
