#include <iostream>
#include <string>

using namespace std;

int test(string& str) {
    cout << "left value ref: " << str << endl;
}
int test(string&& str) {
    str = "hello";
    cout << "right value ref: " << str << endl;
}

int main(int argc, char** argv) {
    test("111");
    string str = "222";
    test(str);

    return 0;
}
