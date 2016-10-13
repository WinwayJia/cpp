#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

class SampleClass {
public:
    SampleClass(int a, double b) {
        this->a = a; 
        this->b = b;
        p = new float();
    }

    virtual ~SampleClass() {
        if (p) {
            delete p;
            p = NULL;
        }
    }

    SampleClass& operator= (const SampleClass& s) {
        //swap<const SampleClass&>(*this, s);
        this->a = s.a;
        this->b = s.b;
        if (p) {
            *p = *s.p;
        } else {
            p = new float(*s.p);
        }

        return *this;
    }

    SampleClass& operator++ () {
        cout << " operator ++it " << endl;
        this->a ++;
        this->b += 1.0;
        return *this;
    }

    SampleClass& operator++ (int) {
        cout << " operator it++ " << endl;
        this->a ++;
        this->b += 1.0;
        return *this;
    }

    string ToString() {
        stringstream ss;
        ss << a << " " << b << " " << *p;
        return ss.str();
    }

private:
    int a;
    double b;
    float* p;
};  

int main(int argc, char** argv) {
    SampleClass sc(1, 2.0);

//    test(++ sc);
//    test(sc ++);
}
