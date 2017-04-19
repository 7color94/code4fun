#include <iostream>
#include <fstream>
using namespace std;

long long s1, s2, v1, v2, m;

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

	ExtendedEuclid(rawA, rawB, x, y);

	x = (x * C) % B;
	while (x < 0) {
		x += B > 0 ? B : -B;
	}

	//cout << x << " " << y << endl;
	return true;
}

int main() {
	long long A, B, C, x, y;
	cin >> s1 >> s2 >> v1 >> v2 >> m;
	
	if (v1 < v2) {
		A = v1 - v2;
		B = m;
		C = s2 - s1;
	} else {
		A = v2 - v1;
		B = m;
		C = s1 - s2;
	}

	if (LinearEquation(A, B, C, x, y)) {
		cout << x << endl;
	} else {
		cout << -1 << endl;
	}
	
	return 0;
}