#ifndef __FOO_H__
#define __FOO_H__
template<typename T>
class foo{
public:
    static void init(){
        return;
    }
};

template<>
void foo<int>::init();

#endif // __FOO_H__

