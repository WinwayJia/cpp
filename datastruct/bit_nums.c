#include <stdio.h>

int main()
{
    int num = 0;
    int v = 1024;
    int cp = v;
    while (v) {
        v &= v - 1;
        num ++;
    }
    printf("1 bit num in %d is %d\n", cp, num);
    return 0;
}
