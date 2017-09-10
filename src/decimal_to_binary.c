#include <stdio.h>

int decimal_to_binary(int n);
int decimal_to_binary_tail(int n, int binary, int i);

int main(){

    printf("%d", decimal_to_binary(63));
	
	printf("\n\nPress ENTER key to Continue\n");
	getchar();

    return 0;
}

int decimal_to_binary(int n) {
     return decimal_to_binary_tail(n, 0, 1);
}

int decimal_to_binary_tail(int n, int binary, int i) {
     return n == 0 ? binary : decimal_to_binary_tail(n / 2, binary + ((n % 2) * i), i * 10);
}
