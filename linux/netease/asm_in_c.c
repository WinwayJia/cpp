#include <stdio.h>

int main(int argc, char** argv) {
    int x = 10;
    int y = 20;
    int z  = x + y;
    printf("%d + %d = %d\n", x, y, z);

    asm (
            "movl %%ecx, %%eax\n"
            "addl %%edx, %%eax\n"
            "movl %%eax, %0\n"
            :"=m"(z)
            :"c"(x),"d"(y)
        );

    printf("%d + %d = %d\n", x, y, z);
    return 0;
}
