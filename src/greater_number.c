#include <stdio.h>

int greater_number(int arr[], int size);
int greater_number_tail(int arr[], int size, int greater, int i);

int main(){

    int arr[] = {0, 1, 2, 3, 4, 51, 6, 7, 8, 9};
    printf("%d", greater_number(arr, sizeof(arr) / sizeof(arr[0])));

	printf("\n\nPress ENTER key to Continue\n");
	getchar();

    return 0;
}

int greater_number(int arr[], int size){
     return greater_number_tail(arr, size, -2147483648, 0);
}

int greater_number_tail(int arr[], int size, int greater, int i){
     if (i == size)
         return greater;

     if (arr[i] > greater)
         greater = arr[i];

     return greater_number_tail(arr, size, greater, i + 1);
}
