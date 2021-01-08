#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>

using namespace std;


class Solution {
    public:
        bool isUgly(int num) {
            if (!num) {
                return false;
            }
            while (num % 2 == 0) {
                num = num >> 1;
            }
            while (num % 3 == 0) {
                num = num / 3;
            } 
            while (num % 5 == 0) {
                num = num / 5;
            }
            return  num == 1;
        }

};

int main(int argc, const char** argv) {
    Solution s;
    cout << s.isUgly(6) << endl;
    cout << s.isUgly(14) << endl;
}
