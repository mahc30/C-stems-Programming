/*
 ============================================================================
 Name        : MergeSort.c
 Author      : Miguel Hincapié
 Description : Recursive Mergesort  implementation in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0])) //Macro to determine size of array
#include <stdbool.h>
#include <time.h>

//Testing function
void printArray(char tag, int array[],int n){
	printf("%c %c",tag, '[');
		for(int i = 0; i < n; i++){
			printf("%d ", array[i]);

		}
		puts("]");
}

void merge(int L[], int R[],int A[], int ls, int rs){
	//Array sizes
	int Ls = ls;
	int Rs = rs;

	int i = 0, j= 0, k = 0;

	while(i < Ls && j < Rs){

		if(L[i] <= R[j]){
			A[k] = L[i++];
 		}
		else{
			A[k] = R[j++];
		}
		k++;
	}

	//if one side is finished first, we still need finish the other
	while(i < Ls){
		A[k] = L[i];
		++k;
		++i;
	}
	while(j < Rs){
		A[k] = R[j];
		++k;
		++j;
	}
}

void mergeSort(int A[], int n){

	if(n < 2){
		return;
	}

	int mid = n/2;
	int left[mid];
	int right[n - mid];

	for(int i = 0; i < mid; i++){
		left[i] = A[i];
	}

	for(int i = mid; i < n; i++){
		right[i - mid] = A[i];
	}

	mergeSort(left, mid);
	mergeSort(right, n - mid);

	int ls = NELEMS(left);
	int rs = NELEMS(right);
	merge(left, right, A, ls, rs);
}

bool isSorted(int array[],int size){
	for(int i = 1; i < size; i++){
		if(array[i] < array[i-1]) return false;
	}
	return true;
}

int main(void) {
	int array[] = {8,2,4,6,7,5,1,9,0,3};
	int n = NELEMS(array);
	printArray('U', array, n);

	// Calculate the time taken by mergeSort()
	clock_t t;
	t = clock();
	mergeSort(array, n);
	t = clock() - t;

	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
   printf("mergeSort() took %f seconds to execute \n", time_taken);

	printArray('S', array, n);

	// Calculate the time taken by isSorted()
		t = clock();
	int isSort = isSorted(array, n);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	printf("mergeSort() took %f seconds to execute \n", time_taken);


	fputs(isSort ? "true" : "false", stdout);

	return EXIT_SUCCESS;
}

