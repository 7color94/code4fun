#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
	int findMaxForm(vector<string>& strs, int m, int n) {
		int dp[105][105];
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < strs.size(); i++) {
			int _m = std::count(strs[i].begin(), strs[i].end(), '0');
			int _n = std::count(strs[i].begin(), strs[i].end(), '1');
			for (int mm = m; mm >= _m; mm--) {
				for (int nn = n; nn >= _n; nn--) {
					dp[mm][nn] = std::max(dp[mm][nn], dp[mm - _m][nn - _n] + 1);
				}
			}
		}
		return dp[m][n];
	}
};

int main() {
	
}