#include<iostream>
#include<string.h>
#include<queue>
#include<math.h>

using namespace std;

struct rank_ {
	int x;
	int y;
	int rank;
	int id;
	rank_() :x(0), y(0), rank(0), id(0) {};
};

rank_ ranks[20000];
char arrays[20000];
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
		ranks[i].rank = arrays[i] - 'a' + 1;
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

int main() {
	int n;
	cin >> n;
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
	for (int i = 1; i <= n; i++) {
		std::cout << heights[i] << " ";
	}
	std::cout << "\n";
	system("pause");
}