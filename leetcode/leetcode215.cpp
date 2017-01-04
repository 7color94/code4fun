#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Solution {
public:
	/*
		类似于快速排序的划分
	*/
	int random_select(vector<int>&nums, int left, int right) {
		//srand(time(NULL)); // Seed the time
		//int pivot = left + (right - left) / 2;
		int pivot = rand() % (right - left + 1) + left;
		int key = nums[pivot];
		nums[pivot] = nums[left];
		nums[left] = key;
		int i = left, j = right + 1;
		while (true) {
			while (nums[++i] <= key) {
				if (i == right) {
					break;
				}
			}
			while (nums[--j] >= key) {
				if (j == left) {
					break;
				}
			}
			if (i >= j) {
				break;
			}
			int tmp = nums[i];
			nums[i] = nums[j];
			nums[j] = tmp;
		}
		int tmp = nums[j];
		nums[j] = nums[left];
		nums[left] = tmp;
		return j;
	}

	int divide_conquer(vector<int>& nums, int k, int left, int right) {
		int pivot = random_select(nums, left, right);
		int n = pivot - left + 1;
		if (n == k) {
			return nums[pivot];
		} else if (n < k) {
			return divide_conquer(nums, k - n, pivot + 1, right);
		} else {
			return divide_conquer(nums, k, left, pivot - 1);
		}
	}

	int findKthLargest(vector<int>& nums, int k) {
		return divide_conquer(nums, nums.size() + 1- k, 0, nums.size() - 1);
	}
};

int main() {
	Solution s;
	vector<int> nums{ 2,1 };
	std::cout << s.findKthLargest(nums, 2) << std::endl;
	system("pause");
}