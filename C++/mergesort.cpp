//============================================================================
// Name        : mergeSort.cpp
// Author      : Miguel Hincapié
// Description : Recursive mergesort implementation in cpp
//============================================================================

#include <iostream>
#include <stdbool.h>
#include <chrono>

using namespace std;

void printArray(int array[], int size){
	cout << "[";
	for(int i = 0; i < size; i++){
		cout << array[i] << ", ";
	}
	cout << "]" << std::endl;
}

inline void swap(int *A, int *B){
	int temp;
	temp = *A;
	*A = *B;
	*B = temp;
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

	int ls = sizeof(left)/sizeof(left[0]);
	int rs = sizeof(right)/sizeof(right[0]);
	merge(left, right, A, ls, rs);
}

inline bool isSorted(int array[],int size){
	for(int i = 1; i < size; i++){
		if(array[i] < array[i-1]) return false;
	}
	return true;
}

int main() {
	int array[] = {0,5,1,9,6,2,8,3,7,4,-213,235,23,23,5,235,23,52,36,25,12,21,5,5,8,141,75,45,867,3,47,45742,412,412553,513,51,51,343};
	int n = sizeof(array)/sizeof(array[0]);

	printArray(array, n);
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	mergeSort(array, n);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	printArray(array, n);

	std::cout << "Time taken by mergeSort = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[nanoseconds]" << std::endl;

	begin = std::chrono::steady_clock::now();
	int isSort = isSorted(array, n);
	end = std::chrono::steady_clock::now();

	if (isSort)
		std::cout << "Is Sorted and took = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[nanoseconds] to test" << std::endl;

	return 0;
}

