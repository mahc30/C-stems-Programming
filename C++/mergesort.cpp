//============================================================================
// Name        : mergeSort.cpp
// Author      : Miguel Hincapié
// Description : Recursive mergesort implementation in cpp
//============================================================================

#include <iostream>

using namespace std;

void printArray(int array[], int size){
	cout << "[";
	for(int i = 0; i < size; i++){
		cout << array[i];
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

int main() {
	int array[] = {0,5,1,9,6,2,8,3,7,4};
	int n = sizeof(array)/sizeof(array[0]);

	printArray(array, n);
	mergeSort(array, n);
	printArray(array, n);
	return 0;
}

