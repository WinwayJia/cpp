/*
 * 给定一个整数 n, 返回从 1 到 n 的字典顺序。
 * 例如，
 * 给定 n =13，返回 [1,10,11,12,13,2,3,4,5,6,7,8,9] 。
 * 请尽可能的优化算法的时间复杂度和空间复杂度。 输入的数据 n 小于等于 5,000,000。
 */
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
        vector<int> lexicalOrder(int n) {
            vector<int> result;
            return result;
        }
};


int main(int argc, const char** argv) {
    Solution s;

    auto r = s.lexicalOrder(231);
    for(auto x : r) {
        cout << x << " ";
    }
    cout << endl;
}
