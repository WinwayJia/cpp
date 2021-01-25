#include <iostream>
#include <string>
#include <list>

using namespace std;

class function_object {
    void operator()() const {
        cout << "str" << endl;
    }
    void operator()(const string &str) const {
        cout << str << endl;
    }
};

int main(int argc, char** argv) 
{
    string str = "Hello";
    list<

    function_object();
    return 0;
}
