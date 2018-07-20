#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
/*
int test(string& str) {
    cout << "left value ref: " << str << endl;

}

int test(string&& str) {
    //    str = "hello";
    cout << "right value ref: " << str << endl;

}
*/
string nowString() {
    stringstream ss;
    for (int i=0; i<128; i++) {
        ss << time(NULL);
    }
    return ss.str();
}

int rfUsage() {

//    test("right value");
    string str = "222";
 //   test(std::move(str));
  //  string now = std::move(nowString());
}

int main(int argc, char** argv) {

    string now2 = nowString();

    clock_t start = clock();
    vector<string> vec;
    for (int i=0; i<1000* 100; i++) {
        //vec.push_back(std::move(nowString()));
        vec.push_back(nowString());
    }

    clock_t end = clock();
    cout << "time: " << end - start << endl;
    return 0;

}
