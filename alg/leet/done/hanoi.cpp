#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>
#include <stack>

using namespace std;

void hanoi(int n, char src, char mid, char dst) {
    if (n == 1) {
//        cout << src << " -> " << dst << endl;
        return ;
    }
    hanoi(n-1, src, dst, mid);
//    cout << src << " -> " << dst << endl;
    hanoi(n-1, mid, src, dst);
}

class Dash {
    public:
        Dash(int _n, char s, char m, char d) : n(_n), src(s), mid(m), dst(d) {}

        int n;
        char src;
        char mid;
        char dst;
};

void hanoiStack(int n, char src, char mid, char dst) {
    stack<Dash> s;
    s.push(Dash(n, src, mid, dst));

    while (!s.empty()) {
        auto d = s.top();
        s.pop();
        if (d.n == 1) {
//            cout << d.src << " -> " << d.dst << endl;
        } else {
            s.push(Dash(d.n-1, d.mid, d.src, d.dst));
            s.push(Dash(1, d.src, d.mid, d.dst));
            s.push(Dash(d.n-1, d.src, d.dst, d.mid));
        }
    }
}

int main(int argc, const char** argv) {
    time_t start = time(NULL);
    hanoi(16, 'A', 'B', 'C');
    time_t end1 = time(NULL);
//    cout << "+++++++++++++++++++++++++" << endl;
    hanoiStack(16, 'A', 'B', 'C');
    cout << "start: " << start << " stop1: " << end1 << " stop2: " << time(NULL) << endl;
    return 0;
}
