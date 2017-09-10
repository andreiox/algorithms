#include <stdio.h>

char* reverse_string(char arr[], int size);
char* reverse_string_tail(char arr[], int p1, int p2);

int main(){

    char arr[] = "github.com/andreiox";
    printf("%s", reverse_string(arr, 19));

	printf("\n\nPress ENTER key to Continue\n");
	getchar();

    return 0;
}

char* reverse_string(char arr[], int size) {
    return reverse_string_tail(arr, 0, size - 1);
}

char* reverse_string_tail(char arr[], int p1, int p2) {
    if (p1 >= p2)
        return arr;

    char c = arr[p1];
    arr[p1] = arr[p2];
    arr[p2] = c;

    return reverse_string_tail(arr, p1 + 1, p2 - 1);
}
