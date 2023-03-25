/* C program for Merge Sort */
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<omp.h>
#define MAX 1000000000
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* create temp arrays */
    	int *Left, *Right;
	Left=(int*)malloc(n1*sizeof(int));
	Right=(int*)malloc(n2*sizeof(int));
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        Left[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        Right[j] = arr[m + 1 + j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (Left[i] <= Right[j]) {
            arr[k] = Left[i];
            i++;
        }
        else {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = Left[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = Right[j];
        j++;
        k++;
    }

	free(Left);
	free(Right);
}
 
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}
 
/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
 
/* Driver code */
int main()
{	

	FILE* fptr;
	long double start,end;
	int *arr;
	arr=(int*)malloc(MAX*sizeof(int));
	
	long long int i;
	int num;
	srand(time(0));
	
  
    //fout=fopen("numbers.csv", "w+");
        
	// Read the input
	for (i = 0; i < MAX; i++) {

		num= rand() % 100000;
			

		// Insert the data to file
		//fout << num << "\n";
		//fwrite(num\n,sizeof(num),-1,1,fout)
		arr[i]=num;
			
	}
	


    //int arr[] = { 12, 11, 13, 5, 6, 7 };
    //int arr_size = sizeof(arr) / sizeof(arr[0]);
 
  	start=omp_get_wtime();
    	
   	 mergeSort(arr, 0, MAX - 1);
	
	end=omp_get_wtime();

	fptr = fopen("logg_serial_codes.txt", "a");
	fprintf(fptr,"---Merge Sort Serial---\n");
	fprintf(fptr,"Array Size : %d  , Time Taken: %Lf\n\n",MAX,end-start);

	fclose(fptr);
    
    printf("Time Taken: %Lf \n",end-start);
	free(arr);
 
    
    //printArray(arr, arr_size);

    return 0;
}
