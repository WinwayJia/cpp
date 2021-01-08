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
        int maxSubArray(vector<int>& nums) {
            int maxSum = nums[0];
            int currSum = nums[0];
            for (int i=1; i < nums.size(); i++) {
                if (currSum < 0) {
                    currSum = 0;
                }
                currSum += nums[i];
                if (currSum > maxSum) {
                    maxSum = currSum;
                }
            }
            return maxSum;
        }
};

int main(int argc, const char** argv) {
    Solution s;

    vector<int> vec = {-1, 0, 2, 3, -5, 2, -5, 9, -10, 2, 4, 4};
    cout << s.maxSubArray(vec) << endl;
}

static int x = []() { 
    std::ios::sync_with_stdio(false); 
    cin.tie(NULL);  
    return 0; 
}();

class Solution {
    public:
        int maxSubArray(vector<int>& nums) {
            int preMax = nums[0], curMax = nums[0];
            for (int i = 1; i < nums.size(); i++){
                preMax = max(nums[i], preMax + nums[i]);
                curMax = max(preMax, curMax);
            }
            return curMax;
        }

};
