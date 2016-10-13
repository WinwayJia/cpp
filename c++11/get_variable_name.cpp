#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> a;
    cout << sizeof(a) << endl;

#define VALUE_NAME(v) #v
    cout << VALUE_NAME(a) << endl;

//    cout << #a << endl; // error
    return 0;
}
