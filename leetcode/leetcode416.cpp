#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int f[20005];
        memset(f, 0, sizeof(f));
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        if (sum % 2 != 0) {
            return false;
        }
        int n = nums.size();
        f[0] = 1;
        for (int i = 0; i < n; i++) {
            //f[nums[i]] = 1; 错误
            for (int j = sum/2; j >= nums[i]; j--) {
                f[j] = f[j] | f[j-nums[i]];
            }
            //f[nums[i]] = 1; 正确
        }
        return f[sum/2];
    }
};

int main() {
    Solution s;
    vector<int> nums{1,2,5};
    std::cout << s.canPartition(nums) << std::endl;
}