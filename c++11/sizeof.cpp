#include <iostream>

using namespace std;

class Test {
public:
    int mix;
    static int cix;

private:
    int xxx;
};

int main(int argc, char** argv) {
    cout << "Test sizeof in c++11"
         << " mix:" << sizeof(Test::mix) << " cix: "
         << sizeof(Test::cix)
         //		<< " xxx: " << sizeof(Test::xxx)
         << endl;

    return 0;
}
