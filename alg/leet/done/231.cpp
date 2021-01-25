#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
    public:
        bool isPowerOfTwo(int n) {
            for (int i=0; i<=32; i++){
                if ((n ^ (1<<i)) == 0) {
                    return true;
                }
            }
            return false;
        }

};


int main(int argc, const char** argv) {
    Solution s;

    cout << s.isPowerOfTwo(3) << endl;
}
