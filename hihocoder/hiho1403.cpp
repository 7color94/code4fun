#include<iostream>
#include<string.h>
#include<queue>
#include<math.h>
#include<algorithm>

using namespace std;

struct rank_ {
	int x;
	int y;
	int rank;
	int id;
	rank_() :x(0), y(0), rank(0), id(0) {};
};

rank_ ranks[20000];
int arrays[20000];
int sa[20000];
int heights[20000];

int sortByXY(rank_ a, rank_ b) {
	if (a.x == b.x) {
		return a.y < b.y;
	}
	return a.x < b.x;
}

int sortById(rank_ a, rank_ b) {
	return a.id < b.id;
}

void rankSort(int n) {
	std::sort(ranks + 1, ranks + n + 1, sortByXY);
	ranks[1].rank = 1;
	int c = 1;
	for (int i = 2; i <= n; i++) {
		if (ranks[i].x != ranks[i - 1].x || ranks[i].y != ranks[i - 1].y) {
			c += 1;
		}
		ranks[i].rank = c;
	}
	std::sort(ranks + 1, ranks + n + 1, sortById);
}

void calRanks(int n) {
	for (int i = 1; i <= n; i++) {
		ranks[i].rank = arrays[i] - 1 + 1;
		ranks[i].id = i;
	}
	for (int k = 0; pow(2.0, k) <= n; k++) {
		for (int i = 1; i <= n; i++) {
			ranks[i].x = ranks[i].rank;
			int idx = i + pow(2.0, k);
			if (idx <= n) {
				ranks[i].y = ranks[idx].rank;
			} else {
				ranks[i].y = 0;
			}
		}
		rankSort(n);
		/*for (int i = 1; i <= n; i++) {
			std::cout << ranks[i].rank << " ";
		}
		std::cout << "\n";*/
	}
}

void calHeights(int n) {
	for (int i = 1, j = 0; i <= n; i++) {
		if (j) {
			j--;
		}
		while (arrays[i + j] == arrays[sa[ranks[i].rank - 1] + j]) {
			j++;
		}
		heights[ranks[i].rank] = j;
	}
}

//可重叠的k次最长重复子串 的长度
//给定一个字符串，求至少出现k次的最长重复子串，这k个子串可以重叠。
bool overlap_k_long_string(int k, int l, int n) {
	int count = 1;
	for (int i = 1; i < n; i++) {
		if (heights[i + 1] >= l) {
			count += 1;
			if (count >= k) {
				return true;
			}
		} else {
			count = 1;
		}
	}
	return false;
}

int solve(int k, int n) {
	int left = 1, right = n;
	while (left < right) {
		int l = left + (right - left + 1) / 2;
		if (overlap_k_long_string(k, l, n)) {
			left = l;
		} else {
			right = l - 1;
		}
	}
	return left;
}

int main() {
	int n, k;
	cin >> n;
	cin >> k;
	memset(arrays, 0, sizeof(arrays));
	for (int i = 1; i <= n; i++) {
		cin >> arrays[i];
	}
	calRanks(n);
	for (int i = 1; i <= n; i++) {
		//std::cout << ranks[i].rank << " ";
		sa[ranks[i].rank] = i;
	}
	/*for (int i = 1; i <= n; i++) {
		std::cout << sa[i] << " ";
	}*/
	memset(heights, 0, sizeof(heights));
	calHeights(n);
	/*for (int i = 1; i <= n; i++) {
		std::cout << heights[i] << " ";
	}*/
	//std::cout << "\n";
	std::cout << solve(k, n) << std::endl;
	//system("pause");
}