// 警惕C++最令人恼怒的解析
#include <fstream>
#include <list>
#include <iostream>
using namespace std;

void test_read_file_list() {
/*    ifstream dataFile("ints.dat");
    list<int> data(istream_iterator<int>(dataFile), // 警告！这完成的并不
    istream_iterator<int>()); // 是像你想象的那样
*/
}
class SampleClass {
};

int f1(double d);
int f2(double (d));
int f3(double);

int g1(double (*pf)());
int g2(double pf());
int g3(double ());

int main(int argc, char** argv) {
    test_read_file_list();

    SampleClass sc();
    return 0;
}
