#include <stdio.h>

void heapsort(int *arr, int size);
void build_max_heap(int *arr, int size);
void extract_max(int *arr, int last_position);
void max_heapfy(int *arr, int last_position, int node);
void exchange(int *arr, int i, int j);
void print_array(int *arr, int size);

int main(){

    int arr[] = { 3, 1, 50, 66, 80, 5, 7, 9, 6, 63, 2, 2, 8, 5, 1000, 54, 23 };
    int size = sizeof(arr) / sizeof(arr[0]);    

    printf("Before: ");
    print_array(arr, size);
    heapsort(arr, size);
    printf("\nAfter: ");
    print_array(arr, size);

    printf("\n\nPress ENTER key to Continue\n");
    getchar();
    
    return 0;
}

void heapsort(int *arr, int size){
    build_max_heap(arr, size);
    int i;
    for(i=size-1; i>0; i--)
        extract_max(arr, i);
}

void build_max_heap(int *arr, int size){
    int last_parent_node = size/2-1;
    int i;
    for(i=last_parent_node; i>=0; i--)
        max_heapfy(arr, size-1, i);
}

void extract_max(int *arr, int last_position){
    exchange(arr, 0, last_position);
    max_heapfy(arr, last_position-1, 0);
}

void max_heapfy(int *arr, int last_position, int node){
    if(node*2+2 <= last_position){

        if(arr[node*2+2] > arr[node*2+1]){
            if(arr[node*2+2] > arr[node]){
                exchange(arr, node, node*2+2);
                max_heapfy(arr, last_position, node*2+2);
            }
        } 
        else if(arr[node*2+1] > arr[node]){
            exchange(arr, node, node*2+1);
            max_heapfy(arr, last_position, node*2+1);
        }
    }
    else if(node*2+1 <= last_position && arr[node] < arr[node*2+1]){
        exchange(arr, node, node*2+1);
        max_heapfy(arr, last_position, node*2*1);
    }
}

void exchange(int *arr, int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void print_array(int *arr, int size){
    int i;
    for(i=0; i<size; i++)
        printf("%d ", arr[i]);
}
