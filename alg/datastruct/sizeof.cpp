#include <iostream>
using namespace std;

void test(char p[8]) {
    cout << sizeof(p) << endl;
}

void test_ref(char (&p)[10]) {
    cout << sizeof(p) << endl;
}

int main(int argc, char** argv) {
    char p[10];
    test(p);

    test_ref(p);
}
