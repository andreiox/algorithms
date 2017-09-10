int binary_search(int arr[], int size, int target);
int binary_search_tail(int arr[], int target, int start, int end);

int main(){

    int arr[] = {0, 1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 50};

    printf("%d", binary_search(arr, sizeof(arr) / sizeof(arr[0]), 50));

    return 0;
}

int binary_search(int arr[], int size, int target){
    return binary_search_tail(arr, target, 0, size - 1);
}

int binary_search_tail(int arr[], int target, int start, int end){
    int mid = (start + end) / 2;
    if(arr[mid] == target)
        return mid;
    if(start == end)
        return -1;

    if (arr[mid] < target)
        start = mid + 1;
    else if (arr[mid] > target)
        end = mid - 1;

    return binary_search_tail(arr, target, start, end);
}
