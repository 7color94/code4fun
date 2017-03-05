#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

//a∗b mod c
int64_t mul_mod(int64_t a, int64_t b, int64_t c) {
	a %= c;
	b %= c;
	int64_t result = 0;
	while (b) {
		if (b & 1) { result += a; result %= c; }
		a <<= 1;
		if (a >= c) a %= c;
		b >>= 1;
	}
	return result;
}

int64_t pow_mod(int64_t a, int64_t b, int64_t n) {
	a %= n;
	int64_t res = 1;
	while (b) {
		if (b & 1) res = mul_mod(res, a, n);
		a = mul_mod(a, a, n);
		b >>= 1;
	}
	return res;
}

int main() {
	ifstream cin("A-large-practice.in");
	ofstream cout("output.txt");
	int T;
	long long MOD = 1000000007;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		long long x, y, z;
		long long a, b;
		cin >> a >> b;
		long long cc = min(a, b);
		long long ans = 0;
		x = mul_mod(mul_mod(mul_mod(a, b, MOD), cc, MOD), cc + 1, MOD);
		x = mul_mod(x, pow_mod(2, MOD - 2, MOD), MOD);
		y = mul_mod(mul_mod(cc, cc + 1, MOD), 2 * cc + 1, MOD);
		y = mul_mod(y, pow_mod(6, MOD - 2, MOD), MOD);
		y = mul_mod(a + b, y, MOD);
		z = mul_mod(pow_mod(mul_mod(cc, cc + 1, MOD), 2, MOD), pow_mod(4, MOD - 2, MOD), MOD);
		ans = MOD + x + z - y;
		cout << "Case #" << t << ": " << ans % MOD << endl;
	}
	return 0;
}