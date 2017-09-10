#include <stdio.h>

int is_palindrome(char arr[], int size);
int is_palindrome_tail(char arr[], int i, int j);

int main(){

    char arr[] = "github.com/andreiox";
    char arr2[] = "abcba";

    printf("%d", is_palindrome(arr, 19));
    printf("\n%d", is_palindrome(arr2, 5));

	printf("\n\nPress ENTER key to Continue\n");
	getchar();

    return 0;
}

int is_palindrome(char arr[], int size) {
    return is_palindrome_tail(arr, 0, size - 1);
}

int is_palindrome_tail(char arr[], int i, int j) {
    if (arr[i] != arr[j])
        return 0;

    if (i >= j)
        return 1;

    return palindrome_tail(arr, i + 1, j - 1);
}
