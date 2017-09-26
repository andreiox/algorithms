#include <stdio.h>

void quicksort(int *arr, int left, int right);
int partition(int *arr, int i, int j);
int get_median(int i, int j, int k);
void exchange(int *arr, int i, int j);
void print_array(int *arr, int size);
void insertion_sort(int *arr, int begin, int end);

// If the size of the array is too low (<= 20) the sort method will use insertion sort instead of quicksort

int main(){

    int size = 24;
    int arr[] = { 5, 4, 6, 8, 11, 22, 66, 77, 88, 11, 0, 2, 6, 4, 97, 115, 332, 10, 54, 89, 78, 21, 20, 75 };
	
    printf("Before: ");
    print_array(arr, size);
    quicksort(arr, 0, size-1);
    printf("\nAfter: ");
    print_array(arr, size);

    printf("\n\nPress ENTER key to Continue\n");
    getchar();
    
    return 0;
}

void insertion_sort(int *arr, int begin, int end){
    int i, j;
    for(i=begin; i<=end; i++){
        for(j=i; j>begin; j--){
            if(arr[j-1] > arr[j]){
                int tmp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = tmp;
            }else{
                break;
            }
        }
    }
}

void quicksort(int *arr, int left, int right){
    if(right - left <= 20){
        insertion_sort(arr, left, right);
        return;
    } 

    int i = partition(arr, left, right);
	
    if(left < i)
        quicksort(arr, left, i);

    if(right > (i + 1))
        quicksort(arr, i + 1, right);
}

int partition(int *arr, int i, int j){
    int pivot = get_median(arr[i], arr[(i+j)/2], arr[j]);

    while(i < j){
        while(arr[i] < pivot) i++;
        while(arr[j] > pivot) j--;

        if(i < j){
            exchange(arr, i, j);
            i++;
            j--;
        }
    }

    return j;
}

int get_median(int i, int j, int k){
    if(i > j){
        if(k > i) return k;
        if(k > j) return k;
        return j;
    }
    else{
        if(k > j) return j;
        if(k > i) return k;
        return i;
    }
}

void exchange(int *arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void print_array(int *arr, int size){
    int i;
    for(i=0; i<size; i++)
    printf("%d ", arr[i]);
}
