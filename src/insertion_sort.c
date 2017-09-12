#include <stdio.h>

void insertion_sort(int *arr, int size);
void print_array(int *arr, int size);

int main(){

    int arr[] = { 2, 1, 8, 2, 6, 8, 9, 7 };
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Before: ");
    print_array(arr, size);
    insertion_sort(arr, size);
    printf("\nAfter: ");
    print_array(arr, size);

    printf("\n\nPress ENTER key to Continue\n");
    getchar();

    return 0;
}

void insertion_sort(int *arr, int size){
    int i, j;
    for(i=0; i<size; i++){
        for(j=i; j>0; j--){
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

void imprime_array(int *arr, int size){
    int i;
    for(i=0; i<size; i++)
        printf("%d ", arr[i]);
}
