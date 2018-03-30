#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>

using namespace std;
class Solution {
    public:
        int addDigits(int num) {
            if (num / 10 > 0) {
                int result = addDigits(num / 10) + (num % 10);
            } else {
                return num % 10;
            }
        }

};


int main(int argc, const char** argv) {
    Solution s;
}
