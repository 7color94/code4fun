#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

'''
Inputs: 1 <= n, m <= 10^9
Outputs: m % 1 + m % 2 + ... + m % n
Samples:
	In: 5 5, Out: 4
	In: 10^8 10^8, Out: 565378460
	In: 10^9 10^9, Out: 644908624
'''

typedef long long LL;
typedef unsigned long long ULL;

const int MOD = 1e9 + 7;

LL mod_pow(LL a, LL b) {
	LL ret = 1;
	while (b > 0) {
		if (b & 1) ret = ret * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return ret;
}

LL solve(LL n, LL m) {
	LL ans = 0;
	LL theta = sqrt(m);
	for (LL i = 1; i <= min(n, theta); i++) {
		ans += ((m % i) % MOD);
		ans %= MOD;
		if (ans < 0) ans += MOD;
	}
	if (n > theta) {
		LL left = m / (theta + 1);
		LL right = m / theta;
		LL start = theta;
		if (right == theta) start--;
		for (LL j = start; j >= 1; j--) {
			LL right = m / j;
			LL left = m / (j + 1) + 1;
			if (n < left) break;
			if (n <= right) right = min(right, n);

			LL right_mod = (m % right) % MOD;
			ans += ((right_mod * ((right - left + 1) % MOD)) % MOD);
			ans %= MOD;
			ans += ( ((right - left) % MOD) * ((right - left + 1) % MOD) % MOD * j % MOD * mod_pow(2, MOD - 2) % MOD);
			ans %= MOD;

			if (n <= right) break;
		}
	}

	return ans;
}


int main() {
	ifstream cin("in.txt");
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		LL n, m;
		cin >> n >> m;
		LL ans = solve(n, m);
		cout << "Case #" << t << ": " << ans << endl;
	}

	return 0;
}