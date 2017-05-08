#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-6;

int T, N;
double X[10010], Y[10010], W[10010];

double calc(double xx, double yy) {
	double res = 0.0;
	for (int i = 0; i < N; i++) {
		res += (max(abs(xx - X[i]), abs(yy - Y[i])) * W[i]);
	}
	return res;
}

double search(double xx) {
	double left = -10000.00, right = 10000.00;
	double m1, m2;
	// while (left + eps < right) {
	int iters = 100;
	while (iters--) {
		m1 = left + (right - left) / 3;
		m2 = right - (right - left) / 3;
		double r1 = calc(xx, m1);
		double r2 = calc(xx, m2);
		if (r1 < r2) right = m2;
		else left = m1;
	}
	return calc(xx, left);
}

double search() {
	double left = -10000.00, right = 10000.00;
	double m1, m2;
	//while (left + eps < right) {
	int iters = 100;
	while (iters--) {
		m1 = left + (right - left) / 3;
		m2 = right - (right - left) / 3;
		double r1 = search(m1);
		double r2 = search(m2);
		if (r1 < r2) right = m2;
		else left = m1;
	}
	return search(left);
}

int main() {
	ifstream cin("B-large-practice.in");
	// ofstream cout("out.txt");
	FILE* pFile = fopen("out.txt", "w");
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> X[i] >> Y[i] >> W[i];
		}

		double ans = search();
		// cout << "Case #" << t << ": " << ans << endl;
		fprintf(pFile, "Case #%d: %.12lf\n", t, ans);
	}
	return 0;
}
