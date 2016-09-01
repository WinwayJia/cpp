// sort algorithm example
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class CTestSort
{
public:
    CTestSort(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
//private:        
    int x;
    int y;
};

ostream& operator<<(ostream& out, CTestSort& val)
{
    out << val.x << " " << val.y;
    return out;
}

bool comp(CTestSort& x, CTestSort&y )
{
//    return x.x < y.x;
    return x.y < y.y;
}

int main () {
    CTestSort v1(20, 20);
    CTestSort v2(10, 70);
    CTestSort v3(30, 10);
    CTestSort v4(40, 40);
    cout << v1 << endl;

    vector<CTestSort> vec;
    vec.push_back(v1);
    vec.push_back(v2);
    vec.push_back(v3);
    vec.push_back(v4);
    vector<CTestSort>::iterator it;


    for (it=vec.begin(); it!=vec.end(); ++it)
        cout << *it << endl;
    sort(vec.begin(), vec.end(), comp);

    cout << "=============\n\n\n";
    for (it=vec.begin(); it!=vec.end(); ++it)
        cout << *it << endl;

    return 0;
}

