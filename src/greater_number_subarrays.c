int subarrays_greater_number(int arr[], int size);
int subarrays_greater_number_tree(int arr[], int i, int j);

int main(){

    int arr[] = {0, 1, 2, 79, 4, -3, 166, 7, 78, 9};
    printf("%d", subarrays_greater_number(arr, sizeof(arr) / sizeof(arr[0])));

    return 0;
}

int subarrays_greater_number(int arr[], int size) {
    return subarrays_greater_number_tree(arr, 0, size - 1);
}

int subarrays_greater_number_tree(int arr[], int i, int j) {
    if (i == j)
        return *arr + i;

    if (j - 1 == i)
        return arr[i] >= arr[j] ? arr[i] : arr[j];

    int mid = (i + j) / 2;
    int n1 = subarrays_greater_number_tree(arr, i, mid);
    int n2 = subarrays_greater_number_tree(arr, mid + 1, j);

    return n1 >= n2 ? n1 : n2;
}
