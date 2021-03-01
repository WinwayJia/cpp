//RUN: clang -fsanitize=address -g memory-leak.c -o memory-leak
#include <stdlib.h>

void *p;

int main() {
    p = malloc(7);
    p = 0; // The memory is leaked here.
    return 0;
}
