#include <stdlib.h>
#include <iostream>
using namespace std;
#define ARR_NUM_SIZE (32)

void swap(int* arr, int x, int y) {
    int tmp = arr[x];
    arr[x] = arr[y];
    arr[y] = tmp;
}
/*
ostream& operator<<(int *arr, int size) {
    for (int i=0; i<size; i++) {
        cout << arr[i] << " " ;
    }
    cout << endl;
}
*/

// ascending order
void quick_sort(int* arr, int start, int end) {
    if (start >= end) {
        return;
    }
    int j = start + 1;
    for (int i=start+1; i<end; i++) {
        if (arr[i] < arr[start]) {
            swap(arr, i, j);
            j++;
        } 
    }
    swap(arr, start, j-1);
    quick_sort(arr, start, j-1);
    quick_sort(arr, j, end);
}

int main(int argc, char** argv) {
    srand(time(NULL));
    int arr[ARR_NUM_SIZE];

    for (int i=0 ;i<ARR_NUM_SIZE; i++) {
        arr[i] = random() % 1024;
    }

    for (int i=0 ;i<ARR_NUM_SIZE; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    quick_sort(arr, 0, ARR_NUM_SIZE);

    for (int i=0 ;i<ARR_NUM_SIZE; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
