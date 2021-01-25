#include <iostream>

using namespace std;

void insertSort(int* arr, int len) {
    int tmp;
    int j;
    for (int i=1; i<len; i++) {
        tmp = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > tmp)  {
            arr[j+1] = arr[j];
            j --;
        }
        arr[j+1] = tmp;
    }
}

void shellSort(int* arr, int len) {
    int step = len / 2;
}

int main() {
    int arr[] = {3, 2, 1, 5, 4};
    insertSort(arr, 5);
    return 0;
}
