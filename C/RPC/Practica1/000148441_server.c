/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "000148441.h"

#ifndef _SERVERAUX
#define _SERVERAUX
int minOdd(int *arr, int size){

    int foundOdd = 0;
    int min = arr[0];

    for(int i = 0; i < size; i++){
        if((arr[i] % 2 == 1 || arr[i] % 2 == -1)  && arr[i] <= min){
            foundOdd = 1;
            min = arr[i];
        }
    }

    if(foundOdd){
        return min;
    }

    return 0;
}

int isPerfect(int n){
    int sum = 0;
    for(int i = 1; i < n; i++){
            if(n % i == 0){
                sum+= i; //Sumar divisor
            }
    }

    if(sum == n){
        return 1;
    }
    return 0;
}

int maxNoPerfect(int *arr, int size){
    int max = arr[0];
    int foundNoPerfect = 0;

    for(int i = 0; i < size; i++){
        if(!isPerfect(arr[i]) && arr[i] > max){
            max = arr[i];
            foundNoPerfect = 1;
        }
    }

    if(foundNoPerfect){
        return max;
    }

    return 0;
}

double medioRangoE(int minOdd, int maxNoPerfect){
    return (minOdd + maxNoPerfect) / 2.0;
}


int productoP(int *arr1, int *arr2, int size){
    int sum = 0;

    for(int i = 0; i < size; i++){
        sum+= arr1[i] * arr2[i];
    }

    return sum;
}
#endif

int *
productopunto_1_svc(arrays *argp, struct svc_req *rqstp)
{
        static int  result;
        
        int *arr1 = argp->arr1;
        int *arr2 = argp->arr2;
        int arr1len = argp->arr1len;

        result = productoP(arr1, arr2, arr1len); 

        return &result;
}

double *
mediorangoespecial_1_svc(arrays *argp, struct svc_req *rqstp)
{
        static double  result;
        
        int *arr1 = argp->arr1;
        int *arr2 = argp->arr2;
        int arr1len = argp->arr1len;
        int arr2len = argp->arr2len;

        result = medioRangoE(minOdd(arr1, arr1len), maxNoPerfect(arr2, arr2len));
        return &result;
}
