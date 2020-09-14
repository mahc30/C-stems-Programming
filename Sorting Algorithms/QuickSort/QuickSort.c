/*
 ============================================================================
 Name        : QuickSort.c
 Author      : Miguel Hincapié
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
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

void swap(int *A, int *B){
	int temp;
	temp = *A;
	*A = *B;
	*B = temp;
}

void quickSort(int A[], int start, int end, int size){

	int left = start, right = end;
	int pivot = A[(left + right)/2];

	while(left <= right){
		while(A[left] < pivot) left++;
		while(A[right] > pivot) right--;

		if(left <= right){
			swap(&A[left], &A[right]);
			left++; right--;
		}
	}

	if(start < right){
		quickSort(A, start, right, size);
	}
	if(left < end){
		quickSort(A, left, end, size);
	}
	//printArray('q', A, size);
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

		// Calculate the time taken by QuickSort()
		clock_t t;
		t = clock();
		quickSort(array, 0, n - 1, n);
		t = clock() - t;

		double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	   printf("QuickSort() took %f seconds to execute \n", time_taken);

		printArray('S', array, n);

		// Calculate the time taken by isSorted()
		t = clock();
		int isSort = isSorted(array, n);
		t = clock() - t;
		time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
		printf("IsSort() took %f seconds to execute \n", time_taken);

		fputs(isSort ? "true" : "false", stdout);

		return EXIT_SUCCESS;
	}
