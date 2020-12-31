#include <iostream>

inline void swap(int* arr, int x, int y) {
    int tmp = arr[x];
    arr[x] = arr[y];
    arr[y] = tmp;
}

// smaller left
int partion(int* arr, int b, int e) {
    if (e <= b) {
        return b;
    }

    int t = arr[b];

    int j = b + 1;
    for (int i=b+1; i<=e; i++) {
        if (arr[i] < t) {
            swap(arr, i, j);
            j ++;
        }
    }

    swap(arr, j-1, b);

    return j - 1;
}

void qsort(int* arr, int b, int e) {
    if (b >= e) {
        return;
    }

    int mid = partion(arr, b, e);
    qsort(arr, b, mid-1);
    qsort(arr, mid+1, e);
    return;
}

int main() {
    int arr[] = {4, 3, 2, 1, 5, 0, 7};
    int len = sizeof(arr) / sizeof(arr[0]);
//    int mid = partion(arr, 0, len-1);
//    printf("mid: %d\n", mid);
    qsort(arr, 0, len-1);

    for (int i=0; i<len; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}

