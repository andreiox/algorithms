#include <stdio.h>

void print_array(int *arr, int size);
void merge_sort(int *arr, int i, int j);
void merge(int *arr, int begin, int mid, int end);

int main(){
    int arr[] = { 5, 4, 6, 8, 11, 22, 66, 77, 88, 11, 0, 2, 6, 4 };
    int size = sizeof(arr) / sizeof(arr[0]);
	
    printf("Before: ");
    print_array(arr, size);

    merge_sort(arr, 0, size-1);

    printf("\nAfter: ");
    print_array(arr, size);

    printf("\n\nPress ENTER key to Continue\n");
    getchar();

    return 0;
}

void merge_sort(int *arr, int i, int j){
    if(i>=j)
        return;

    int mid = (i+j)/2;
    merge_sort(arr, i, mid);
    merge_sort(arr, mid+1, j);

    merge(arr, i, mid, j);
}

void merge(int *arr, int begin, int mid, int end){
    int i = begin;
    int j = mid+1;
    int aux[end-begin+1];
    int k = 0;

    while(i <= mid && j <= end){
        if(arr[i] < arr[j]){
            aux[k] = arr[i];
            i++;
        }else{
            aux[k] = arr[j];
            j++;
        }

        k++;
    }

    while(i<=mid){
        aux[k] = arr[i];
        k++; i++;
    }

    while(j<=end){
        aux[k] = arr[j];
        k++; j++;
    }

    k = 0;
    while(k+begin<=end){
        arr[k+begin] = aux[k];
        k++;
    }

}

void print_array(int *arr, int size){
    int i;
    for(i=0; i<size; i++)
        printf("%d ", arr[i]);
}
