//============================================================================
// Name        : quickSort.cpp
// Author      : Miguel Hincapié
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdbool.h>
#include <chrono>

//Testing function
inline void printArray(char tag, int array[],int n){
	printf("%c %c",tag, '[');
		for(int i = 0; i < n; i++){
			printf("%d ", array[i]);

		}
		puts("]");
}

inline void swap(int *A, int *B){
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

}

inline bool isSorted(int array[],int size){
	for(int i = 1; i < size; i++){
		if(array[i] < array[i-1]) return false;
	}
	return true;
}

int main(void) {


	int array[] = {8,2,4,6,7,5,1,9,0,3};
		int n = sizeof(array) /sizeof(array[0]);
		printArray('U', array, n);

		// Calculate the time taken by QuickSort()
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		quickSort(array, 0, n - 1, n);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << "Time taken by mergeSort = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[nanoseconds]" << std::endl;

		printArray('S', array, n);

		// Calculate the time taken by isSorted()
		begin = std::chrono::steady_clock::now();
		int isSort = isSorted(array, n);
		end = std::chrono::steady_clock::now();
		if (isSort)
				std::cout << "Is Sorted and took = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[nanoseconds] to test" << std::endl;



		return EXIT_SUCCESS;
	}
