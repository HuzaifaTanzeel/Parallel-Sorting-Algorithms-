// C++ program to implement the Quick Sort
// using OMP
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#define MAX 500000000
int x;

void swap(int *a,int *b);
int partition(int arr[], int start, int end);
void quickSort(int arr[], int start, int end);

// Driver Code
int main()
{
	FILE *fptr;
	long double start,end;
	int *arr;
	arr=(int*)malloc(MAX*sizeof(int));
	long long int i;
	int num;
	srand(time(0));
	for (i = 0; i < MAX; i++) {
		num= rand() % 100000;
		arr[i]=num;		
	}
    start=omp_get_wtime();
    //#pragma omp parallel 
    //{
	x=omp_get_num_threads();
        //#pragma omp single
        quickSort(arr, 0, MAX-1);
    //}   
	end=omp_get_wtime();
	fptr=fopen("logg_quick.txt","a");
fprintf(fptr,"Array size: %d , Threads: %d , Time taken: %.2Lf sec \n",MAX,x,end-start);
    printf("Array size: %d , Threads: %d , Time taken: %.2Lf sec\n",MAX,x,end-start);
    free(arr);
    return(0);
}

// Function to swap two numbers a and b
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
// Function to perform the partitioning
// of array arr[]
int partition(int arr[], int start, int end){
	// Declaration
	int pivot = arr[end];
	int i = (start - 1);
	// Rearranging the array
	for (int j = start; j <= end - 1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[end]);
	// Returning the respective index
	return (i + 1);
}
// Function to perform QuickSort Algorithm
// using openmp
void quickSort(int arr[], int start, int end){
	// Declaration
	int index;
	if (start < end) {
		// Getting the index of pivot
		// by partitioning
		index = partition(arr, start, end);
// Parallel sections
#pragma omp parallel sections
		{
#pragma omp section
			{
				// Evaluating the left half
				quickSort(arr, start, index - 1);
			}
#pragma omp section
			{
				// Evaluating the right half
				quickSort(arr, index + 1, end);
			}
		}
	}
}

