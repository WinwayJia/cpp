// 有一个很大的文件，存放一堆7位的电话号码，号码无重复，请用最小的内存消耗，将其排序。
#include <stdio.h>
#include <alloca.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DEF_MIN_NUMBER (10000)
#define DEF_MAX_NUMBER (100000)

unsigned char bits[] = {
    0x01, 0x02, 0x04, 0x08,
    0x10, 0x20, 0x40, 0x80, 
};

void swap(int* arr, int i, int j) 
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

// 乱序，类似于扑克洗牌
int unorder(int* arr, int size)
{
    int rand = 0;
    for (int i=size-1; i>0; i--) {
        rand = random() % i;
        swap(arr, i, rand);
    }

    return 0;
}

int bitmap_sort(int *arr, int size)
{
    int index, pos;
    unsigned char* bitmap = (unsigned char*)alloca(size/8+1);
    memset(bitmap, 0, size/8+1);
    for (int i=0; i<size; i++) {
        index = (arr[i]-DEF_MIN_NUMBER) / 8;
        pos = (arr[i]-DEF_MIN_NUMBER) % 8;
        bitmap[index] |= bits[pos];
    }

    for (int i=0; i<size/8+1; i++) {
        if (bits[0]&bitmap[i]) {
            printf("%d ", i * 8 + 0 + DEF_MIN_NUMBER);
        }
        if (bits[1]&bitmap[i]) {
            printf("%d ", i * 8 + 1 + DEF_MIN_NUMBER);
        }
        if (bits[2]&bitmap[i]) {
            printf("%d ", i * 8 + 2 + DEF_MIN_NUMBER);
        }
        if (bits[3]&bitmap[i]) {
            printf("%d ", i * 8 + 3 + DEF_MIN_NUMBER);
        }
        if (bits[4]&bitmap[i]) {
            printf("%d ", i * 8 + 4 + DEF_MIN_NUMBER);
        }
        if (bits[5]&bitmap[i]) {
            printf("%d ", i * 8 + 5 + DEF_MIN_NUMBER);
        }
        if (bits[6]&bitmap[i]) {
            printf("%d ", i * 8 + 6 + DEF_MIN_NUMBER);
        }
        if (bits[7]&bitmap[i]) {
            printf("%d ", i * 8 + 7 + DEF_MIN_NUMBER);
        }
    }
    putchar('\n');

    return 0;
}

int main(int argc, char** argv) 
{
    srandom(time(NULL));
    int* phone_number = alloca((DEF_MAX_NUMBER-DEF_MIN_NUMBER) * sizeof(int));
    for (int i=DEF_MIN_NUMBER; i<DEF_MAX_NUMBER; i++) {
        phone_number[i-DEF_MIN_NUMBER] = i;
    }
    printf("init: \n");
    for (int i=DEF_MIN_NUMBER; i<DEF_MAX_NUMBER; i++) {
        printf("%d ", phone_number[i-DEF_MIN_NUMBER]);
    }
    printf("\n\n");

    unorder(phone_number, DEF_MAX_NUMBER-DEF_MIN_NUMBER);
    printf("unorder: \n");
    for (int i=DEF_MIN_NUMBER; i<DEF_MAX_NUMBER; i++) {
        printf("%d ", phone_number[i-DEF_MIN_NUMBER]);
    }

    printf("\n\n");

    printf("order: \n");
    bitmap_sort(phone_number, DEF_MAX_NUMBER-DEF_MIN_NUMBER);

    return 0;
}
