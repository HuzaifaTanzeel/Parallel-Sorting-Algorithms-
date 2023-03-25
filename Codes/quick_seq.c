#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<omp.h>
#define MAX 500000000


// function to swap elements
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(int array[], int low, int high) {
  
  // select the rightmost element as pivot
  int pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);
    
    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);
    
    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}


// main function
int main() {

	FILE* fptr;
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

  quickSort(arr, 0, MAX - 1);
  
  end=omp_get_wtime();

	fptr = fopen("logg_serial_codes.txt", "a");
	//fprintf(fptr,"---Quick Sort Serial---\n");
	fprintf(fptr,"Array Size : %d  , Time Taken: %Lf\n\n",MAX,end-start);

	fclose(fptr);
    
    printf("Time Taken: %Lf \n",end-start);
	free(arr);
 
    
    

    return 0;
}
