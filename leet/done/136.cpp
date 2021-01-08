#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>

using namespace std;


class Solution {
    public:
        int singleNumber(vector<int>& nums) {
            int result = 0;
            for (auto &i : nums) {
                result ^= i;
            }
            return result;
        }
};

int main(int argc, const char** argv) {
    Solution s;
    vector<int> vec = {1, 2, 1, 2, 3};
    cout << s.singleNumber(vec) << endl;
}
