#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#define TOP_K (8)

#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)

int show(int *arr, int len) {
    for (int i=0; i<len; i++) {
        printf("%d ", arr[i]);
    }
    puts("");
}


void swap(int* arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void heapify(int arr[], int len, int i) {
    int largest = i;
    if (LEFT(i) < len && arr[i] > arr[LEFT(i)]) {
        largest = LEFT(i);
    }
    if (RIGHT(i) < len && arr[largest] > arr[RIGHT(i)]) {
        largest = RIGHT(i);
    }

    if (largest != i) {
        swap(arr, i, largest);
        heapify(arr, len, largest);
    }
}

void build_heap(int arr[TOP_K], int len) {
    for (int i=len/2; i>=0; i--) {
        heapify(arr, len, i);
    }
}

static int top[TOP_K];
// top k greater number
void topk(int x) {
    static int count  = 0;
    if (count < TOP_K) {
        top[count++] = x;
        if (TOP_K == count) {
            build_heap(top, TOP_K);
        }
        return ;
    }

    if (x > top[0]) {
        top[0] = x;
        heapify(top, TOP_K, 0);
    }
}

int main(int argc, char** argv) {
    FILE* fp = fopen(argv[1], "r");
    if (NULL == fp) {
        printf("fopen failed: %s\n", strerror(errno));
        exit(-1);
    }

    char buff[1024];
    while(fgets(buff, sizeof(buff), fp) != NULL) {
        topk(atoi(buff));
    }

    fclose(fp);

    show(top, TOP_K);
}
