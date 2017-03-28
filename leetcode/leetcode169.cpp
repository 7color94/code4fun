#include<iostream>
#include<time.h>
#include<vector>

using namespace std;

class Solution {
public:
	int majorityElement(vector<int>& nums) {
		int major = 0, n = nums.size();
		for (int i = 0, mask = 1; i < 32; i++, mask <<= 1) {
			int bitCounts = 0;
			for (int j = 0; j < n; j++) {
				if (nums[j] & mask) bitCounts++;
				if (bitCounts > n / 2) {
					major |= mask;
					break;
				}
			}
		}
		return major;
	}
};

int main() {
	Solution s;
	vector<int> nums{1,1,3,3,3};
	int major = s.majorityElement(nums);
	std::cout << major << std::endl;
}
