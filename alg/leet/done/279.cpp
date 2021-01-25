#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

class Solution {
    public:
        int bfs(const vector<int>& nums, int n) {
            int ans = 0x7FFFFFFF;
            for (auto i : nums) {
                if (i == n) {
                    return 1;
                }
                if (i < n) {
                    ans = min(bfs(nums, n-i)+1, ans);
                }
            }

            return ans;
        }

        int numSquares(int n) {
            int ans = 0;
            vector<int> nums;
            for (int i=1; ; i++) {
                int tmp = i * i;
                if (tmp > n) {
                    break;
                }
                nums.push_back(tmp);
            }

            return bfs(nums, n);
        }

        int numSquaresDP(int n) {
            vector<int> nums;
            for (int i=1; ; i++) {
                int tmp = i * i;
                if (tmp > n) {
                    break;
                }
                nums.push_back(tmp);
            }

            vector<int> ans;
            ans.reserve(n+1);
            ans[1] = 1;
            for (int i=2; i<=n; i++) {
                int res = 0x7FFFFFFF;
                for (auto x : nums) {
                    if (i == x) {
                        res = 1;
                        break;
                    } else if (i > x) {
                        res = min(ans[i-x] + 1, res);
                    } else {
                        break;
                    }
                }
                ans[i] = res;
            }
            return ans[n];
        }
};

int main(int argc, const char** argv) {
    Solution s;
    cout << 15 << ": " << s.numSquares(15) << endl;
    cout << 7 << ": " << s.numSquares(7) << endl;
    cout << 8 << ": " << s.numSquares(8) << endl;
    cout << 12 << ": " << s.numSquares(12) << endl;

    cout << "DP:" << endl;
    cout << 15 << ": " << s.numSquaresDP(15) << endl;
    cout << 7 << ": " << s.numSquaresDP(7) << endl;
    cout << 8 << ": " << s.numSquaresDP(8) << endl;
    cout << 12 << ": " << s.numSquaresDP(12) << endl;
}
