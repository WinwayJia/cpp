#include <stdio.h>

#include <iostream>
using namespace std;

class TestStatic {
public:
    TestStatic() {}
    int init() {
        for (int i = 0; i < 32; i++) {
            snprintf(m_prefix[i], 128, "prefix: %02d", i);
        }
        return 0;
    }
    int showStatic() {
        for (int i = 0; i < 32; i++) {
            cout << m_prefix[i] << endl;
        }
        return 0;
    }
    static char m_prefix[32][128];

protected:
private:
};

char TestStatic::m_prefix[32][128];

int main(int argc, char** argv) {
    TestStatic ts;

    ts.init();
    ts.showStatic();

    cout << TestStatic::m_prefix[0] << endl;
    return 0;
}
