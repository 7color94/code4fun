#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

int T;
int N, P, W, H;
int paragraph[1005];

// Wrong Answer
int solve(int font) {
	long long ww = floor(W * 1.0 / font);
	long long hh = floor(H * 1.0 / font);
	int pages = 0, idx = 0;
	long long ch = 1;
	long long chars = paragraph[idx];
	while (true) {
		long long nh = ceil((chars * 1.0) / ww);
		if (nh > (hh - ch + 1)) {
			pages++;
			ch = 1;
			chars -= ww * (hh - ch + 1);
		} else {
			idx++;
			if (idx >= N) break;
			chars = paragraph[idx];
			ch += nh;
			if (ch > hh) {
				ch = 1;
				pages++;
			}
		}
	}
	return pages;
}

int check(int font) {
	int ww = floor(W * 1.0 / font);
	int hh = floor(H * 1.0 / font);
	long long sum = 0;
	for (int i = 0; i < N; i++) {
		int hang = ceil(1.0 * paragraph[i] / ww);
		sum += hang;
	}
	int page = ceil(1.0 * sum / hh);
	return page;
}

int binary_search() {
	int left = 1, right = min(W, H);
	int ans = 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (solve(mid) <= P) {
			ans = max(mid, ans);
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return ans;
}

int main() {
	ifstream cin("in.txt");
	cin >> T;
	while (T--) {
		cin >> N >> P >> W >> H;
		for (int i = 0; i < N; i++) {
			cin >> paragraph[i];
		}

		int ans = binary_search();
		cout << ans << endl;
	}

	return 0;
}