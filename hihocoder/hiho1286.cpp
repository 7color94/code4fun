#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <climits>
#include <string>
#include <fstream>
using namespace std;

long long Q, N, M, K;

long long gcd(long long a, long long b) {
	return b == 0 ? a : gcd(b, a % b);
}

void ExtendedEuclid(long long A, long long B, long long& x, long long& y) {
	if (B == 0) {
		x = 1;
		y = 0;
		return;
	}
	ExtendedEuclid(B, A % B, x, y);
	long long tmp = x;
	x = y;
	y = tmp - (A / B) * y;
}

bool LinearEquation(long long A, long long B, long long C, long long& x, long long& y) {
	long long rawA = A, rawB = B, rawC = C;
	long long D = gcd(A, B);

	if (C % D) {
		return false;
	}

	A = A / D;
	B = B / D;
	C = C / D;

	ExtendedEuclid(A, B, x, y);
	
	// 防止溢出 % B
	x = ((x % B) * (C % B)) % B;
	while (x < 0) {
		x += B > 0 ? B : -B;
	}
	y = (rawC - rawA*x) / rawB;
	//cout << "shit " << x << " " << y << endl;
	return true;
}

// calculate A11 p*q
long long calA11pq(long long p, long long q) {
	if (q <= p) return (1 + q)*q / 2 * p - (q - 1)*q*(q + 1) / 6;
	else return calA11pq(p, p) + (q - p)*(p + 1)*p / 2;
}

// calculate A1j N*M
long long calA1jNM(long long i, long long j) {
	// A11 N*(M+j-1) - A11 N*(j-1)
	return calA11pq(N, M + j - 1) - calA11pq(N, j - 1);
}

// calculate Ai1 N*M
long long calAi1NM(long long i, long long j) {
	// Ai1 (N+i-1)*M - A11 (i-1)*M
	return calA11pq(N + i - 1, M) - calA11pq(i - 1, M);
}

void solve() {
	long long ansx, ansy, S, x, y, flag;
	bool find = false;

	// S11..S12...S1N
	for (int t = 1; t <= N; t++) {
		S = calA1jNM(1, t);

		/*
		long long t_S = 0;
		for (int i = 1; i <= N; i++) {
		for (int j = t; j <= t + M - 1; j++) {
		t_S += min(i, j);
		}
		}
		*/
		//cout << "1 row " << t << " col" << endl;
		//cout << "S= " << S << " " << "t_S= " << t_S << endl;

		flag = LinearEquation(-N*M, K, S, x, y);
		if (flag && y > 0 && x >= 0) {
			int nx = 1 + x;
			int ny = t + x;
			if (!find) {
				ansx = nx;
				ansy = ny;
				find = true;
			}
			else {
				if (nx + ny < ansx + ansy) {
					ansx = nx;
					ansy = ny;
				}
				if (nx + ny == ansx + ansy && nx < ansx) {
					ansx = nx;
					ansy = ny;
				}
				if (1 + t > ansx + ansy) {
					break;
				}
			}
		}
	}

	// S11..S21...SM1
	for (int t = 1; t <= M; t++) {
		S = calAi1NM(t, 1);

		x = -1; y = -1;

		flag = LinearEquation(-N*M, K, S, x, y);
		if (flag && y > 0 && x >= 0) {
			int nx = t + x;
			int ny = 1 + x;
			if (!find) {
				ansx = nx;
				ansy = ny;
				find = true;
			}
			else {
				if (nx + ny < ansx + ansy) {
					ansx = nx;
					ansy = ny;
				}
				if (nx + ny == ansx + ansy && nx < ansx) {
					ansx = nx;
					ansy = ny;
				}
				if (1 + t > ansx + ansy) {
					break;
				}
			}
		}
	}

	if (!find) {
		cout << -1 << endl;
	}
	else {
		cout << ansx << " " << ansy << endl;
	}

	return;
}

int main() {
	ifstream cin("in.txt");

	cin >> Q;
	while (Q--) {
		cin >> N >> M >> K;
		solve();
	}

	return 0;
}
