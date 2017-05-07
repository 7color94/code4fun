#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

/*
Problem: https://codejam.withgoogle.com/codejam/contest/11304486/dashboard#s=p0
Solution: http://blog.csdn.net/w57w57w57/article/details/6657547
But this solution is TLE for large data set. But the solution about using bit operation to calculate combination problems is great.
*/

int T, N;
int numbers[10005];

int solve(int C) {
	int i = 0;
	int k;
	int minn = 10010, maxn = 0;
	while ((k = 1 << i) <= C) {
		if ((C & k) != 0) {
			minn = min(minn, numbers[i]);
			maxn = max(maxn, numbers[i]);
			// cout << numbers[i] << " ";
		}
		i++;
	}
	return (maxn - minn) % 1000000007;
}

int nextN(int C) {
	return (C + (C & (-C))) | ((C ^ (C + (C &(-C)))) / (C & (-C))) >> 2;
}

int subset() {
	int ans = 0;
	int i = 1;
	while (i <= N) {
		int c = (1 << i) - 1;
		while (c <= (1 << N) - 1) {
			int _ans = solve(c);
			ans = (ans + _ans) % 1000000007;
			c = nextN(c);
		}
		i++;
	}
	return ans;
}

int main() {
	ifstream cin("A-large.in");
	ofstream cout("out.txt");
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> numbers[i];
		}
		int ans = subset();
		cout << "Case #" << t << ": " << ans << endl;
	}
	return 0;
}