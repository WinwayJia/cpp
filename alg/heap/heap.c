#include <stdio.h>
#include <stdlib.h>

#define LEFT_LEAF(i) (i*2 + 1)
#define RIGHT_LEAF(i) ((i+1) * 2)

void swap(int *arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int show(int *arr, int len) {
    for (int i=0; i<len; i++) {
        printf("%d ", arr[i]);
    }
    puts("\n");
}

void heapify(int arr[], int len, int i) { 
    int largest = i;
    if (LEFT_LEAF(i) < len && arr[largest] > arr[LEFT_LEAF(i)]) {
        largest = LEFT_LEAF(i);
    }
    if (RIGHT_LEAF(i) < len && arr[largest] > arr[RIGHT_LEAF(i)]) {
        largest = RIGHT_LEAF(i);
    }

    if (largest != i) {
        swap(arr, i, largest);
        heapify(arr, len, largest);
    }
}

void build_heap(int arr[], int len) {
    for (int i=len/2; i>=0; i--) {
        heapify(arr, len, i);
    }
}

void heap_sort(int arr[], int len) {
    for (int i=0; i<len; i++) {
        swap(arr, 0, len-i-1);
        heapify(arr, len-i-1, 0);
    }
}

#define ARRAY_SIZE (32)
int main() {
    int arr[ARRAY_SIZE];
    for (int i=0; i<ARRAY_SIZE; i++) {
        arr[i] = random() & 1023;
    }
show(arr, ARRAY_SIZE);
    
    build_heap(arr, ARRAY_SIZE);
show(arr, ARRAY_SIZE);

    heap_sort(arr, ARRAY_SIZE);
show(arr, ARRAY_SIZE);

    return 0;
}
