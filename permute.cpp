// 减治+递归
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

template<typename T>
std::ostream& operator <<(std::ostream& os, std::vector<T>& vec) {
    for (auto& n : vec) {
        os << n;
    }
    return os;
}

void permute(std::vector<int>& nums, int start, int end, std::vector<std::vector<int>>& result) {
    if (start == end) {
        result.push_back(nums);
        return;
    }

    for (int i=start; i<end; i++) {
        std::swap(nums[start], nums[i]);
        permute(nums, start+1, end, result);
        std::swap(nums[start], nums[i]);
    }
}

// 字典序下一个 132
std::vector<int> nextPermute(const std::vector<int>& curr) {
    std::function<int(int idx)> nearest = [&curr](int idx) {
        int diff = INT32_MAX;
        int result = -1;
        for (int i=idx+1; i<curr.size(); i++) {
            int tmp = curr[i] - curr[idx];
            if (tmp > 0 && tmp < diff) {
                result = i;
            }
        }
        return result;
    };

    std::vector<int> ans = curr;
    bool flag = false;
    for (int i=curr.size()-2; i>=0; i--) {
        auto pos = nearest(i);
        // std::cout << "pos: " << pos << std::endl;
        if (pos >= 0) {
            flag = true;
            std::swap(ans[i], ans[pos]);
            std::sort(ans.begin()+i+1, ans.end(), [](const int& x, const int& y)->bool {
                return x - y;
            });
            break;
        }
    }
    if (!flag) {
        return std::vector<int>{};
    }

    return ans;
}

int main(int argc, char** argv) {
    std::vector<int> nums{1,2,3};
    std::vector<std::vector<int>> ans;
    permute(nums, 0, 3, ans);

    for (auto& item : ans) {
        std::cout << item << std::endl;
    }

    std::cout << "Next: " << std::endl;
    auto next = nums;
    next = {1,2,3,4,5,6};
    while (1) {
        std::cout << next << std::endl;
        next = nextPermute(next);
        if (next.empty()) {
            break;
        }
    }

    return 0;
}