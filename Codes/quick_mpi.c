#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#define MAX 1000000

void swap (int* i, int* j) {
		int temp = *i;
		*i = *j;
		*j = temp;
}

int partition (int arr[], int first, int last) {
		int pivot = arr[last]; // last element is the pivot
		int store_index = first - 1; 
		for (int i = first; i < last; i++) {
			if (arr[i] <= pivot) {
				store_index += 1;
				swap(&arr[store_index], &arr[i]);
			}
		}
		swap(&arr[store_index + 1], &arr[last]);
		return store_index + 1;
}

void quicksort(int arr[], int first, int last) {
		int partition_index;
		if (first < last) {
			partition_index = partition(arr, first, last);
			quicksort(arr, first, partition_index - 1);
			quicksort(arr, partition_index + 1, last);
		}
}



int main(int argc, char* argv[])
{
FILE *fptr;
MPI_Init(NULL,NULL);
int my_rank,no_proc;
long double start, end;
int *arr;
arr=(int*)malloc(MAX*sizeof(int));
long long int i;
int num;
srand(time(0));
for(i=0;i<MAX;i++){
num=rand()%100000;
arr[i]=num;
}
MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
MPI_Comm_size(MPI_COMM_WORLD,&no_proc);
int partition_size=MAX/no_proc;
start=MPI_Wtime();
int *local_array;
local_array=(int*)malloc(partition_size * sizeof(int));
MPI_Scatter(arr,partition_size,MPI_INT,local_array,partition_size,MPI_INT,0,MPI_COMM_WORLD);
quicksort(local_array,0,(partition_size-1));
int *final_arr;
if(my_rank==0){
final_arr=(int*)malloc(MAX*sizeof(int));
}
MPI_Gather(local_array,partition_size,MPI_INT,final_arr,partition_size,MPI_INT,0,MPI_COMM_WORLD);
if(my_rank==0){
quicksort(final_arr,0,(MAX-1));
end=MPI_Wtime();
fptr=fopen("logg_quick.txt","a");
fprintf(fptr,"Array size: %d , Processes: %d , Time taken: %.2Lf sec \n",MAX,no_proc,end-start);
printf("Array size: %d , Processes: %d , Time taken: %.2Lf sec \n",MAX,no_proc,end-start);
printf("\n");
free(final_arr);
}
free(arr);
free(local_array);



MPI_Barrier(MPI_COMM_WORLD);

MPI_Finalize();
}
