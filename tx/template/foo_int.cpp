#include "foo.h"
#include<stdio.h>

template<>
void foo<int>::init(){
    printf("init int foo\n");
}
