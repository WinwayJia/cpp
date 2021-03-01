#include <stdio.h>
#include <ucontext.h>
#include <list>

static __thread std::list<ucontext_t*> t_list;

void f1() {
    while (1) {
        printf("f1\n");
    }
}

int main() {
    int idx = 0;
    ucontext_t ctx;
    getcontext(&ctx);
    printf("idx = %d\n", idx);
    idx ++;
    if (idx < 10) {
        setcontext(&ctx);
    }
    return 0;
}

