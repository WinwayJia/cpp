#include <iostream>
#include <string>
using namespace std;

template <int SIZE, class T>
class CTemplate {
public:
    CTemplate() { cout << SIZE << endl; }
};

int main(int argc, char** argv) {
    CTemplate<100, string> loTem;

    return 0;
}
