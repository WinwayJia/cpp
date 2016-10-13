#include <stdio.h>

int main(int argc, char** argv)
{
   // unsigned 
    int i = 1, j = 1;
    int pos = atoi(argv[1]);
    i <<= pos;
    j <<= 35;

    printf("i = %d j = %d\n", i, j);
    return 0;
}
