#include "foo.h"
#include<stdio.h>

template<>
void foo<float>::init(){
    printf("init float foo\n");
}
