#include <limits>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    cout << numeric_limits<int>::max() << endl;
    cout << numeric_limits<int>::min() << endl;
    cout << numeric_limits<unsigned int>::max() << endl;
    cout << numeric_limits<unsigned int>::min() << endl;
    
    return 0;
}
