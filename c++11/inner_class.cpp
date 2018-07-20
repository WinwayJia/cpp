#include <iostream>
#include <sstream>
#include <stdint.h>
using namespace std;

class Mutex;

class Mutex::impl {
    public:
        string dumps() const {
            stringstream ss;
            ss << "max: " << max_;
            return ss.str();
        }

    private:
        int32_t   max_;
};


class Mutex {
    public:
        string dumpsImpl() const {
            return impl_.dumps();
        }
    private:
        class impl;
        impl impl_;
};

int main() {
    Mutex mx;
    cout << mx.dumpsImpl() << endl;
}
