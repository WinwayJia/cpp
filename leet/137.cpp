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
        int singleNumber(vector<int>& nums) {
            unordered_map<int, int> times;
            for (auto &num : nums) {
                times[num] ++;
                if (times[num] >= 3) {
                    times.erase(num);
                }
            }
            for (auto it=times.begin(); it!=times.end(); it++) {
                if (it->second == 1) {
                    return it->first;
                }
            }

        }
        int singleNumber2(vector<int>& nums) {
            int ans = 0;
            int n = nums.size();
            for (int i = 0; i < 32; i++) {
                int cnt = 0, bit = 1 << i;
                for (int j = 0; j < n; j++) {
                    if (nums[j] & bit) cnt++;
                }
                if (cnt % 3 != 0) {
                    ans |= bit;
                }
            }
            return ans;
        }
        // http://www.cnblogs.com/daijinqiao/p/3352893.html
//对于除出现一次之外的所有的整数，其二进制表示中每一位1出现的次数是3的整数倍，将所有这些1清零，剩下的就是最终的数。
//用ones记录到当前计算的变量为止，二进制1出现“1次”（mod 3 之后的 1）的数位。用
//twos记录到当前计算的变量为止，二进制1出现“2次”（mod 3 之后的 2）的数位。当
//ones和twos中的某一位同时为1时表示二进制1出现3次，此时需要清零。即用二进制模拟三进制计算。最终ones记录的是最终结果。
        int singleNumber3(vector<int>& nums) {
            int ones = 0, twos = 0, xthrees = 0;
            for(int i = 0; i < nums.size(); ++i) {
                twos |= (ones & nums[i]);
                ones ^= nums[i];
                xthrees = ~(ones & twos);
                ones &= xthrees;
                twos &= xthrees;
            }

            return ones;
        }
};

int main(int argc, const char** argv) {

    vector<int> vec = {1,2,2,1,2,1,4,4,4,3};
    Solution s;
    cout << s.singleNumber(vec) << endl;
    cout << s.singleNumber2(vec) << endl;
    cout << s.singleNumber3(vec) << endl;
}






















