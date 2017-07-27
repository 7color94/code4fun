#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <cstring>
#include <cmath>
#include <climits>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;

long long m[1005], r[1005];
int n;

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

// 线性方程组
bool LinearEquation(long long A, long long B, long long C, long long& x, long long& y) {
    // long long rawA = A, rawB = B, rawC = C;
    long long D = gcd(A, B);
    if (C % D) return false;
    A = A / D;
    B = B / D;
    C = C / D;
    ExtendedEuclid(A, B, x, y);
    // 溢出??
    x = (x * C) % B;
    while (x < 0) x += B > 0 ? B : -B;
    return true;
}

// 模线性方程组
long long ModLinearEquation() {
    long long M = m[1], R = r[1];
    for (int i = 2; i <= n; i++) {
        long long D = gcd(M, m[i]);
        long long C = r[i] - R;
        if (C % D) return -1;
        long long k1, k2;
        ExtendedEuclid(M/D, m[i]/D, k1, k2);
        k1 = (C/D * k1) % (m[i] / D);
        R = R + k1 * M;
        M = M / D * m[i];
        // M = M * m[i] / D; // 溢出
        R %= M;
    }
    if (R < 0) R = R + M;
    return R;
}

int main() {
    ifstream cin("in.txt");
    // freopen("in.txt", "r", stdin);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> m[i] >> r[i];
    }
    long long ans = ModLinearEquation();
    cout << ans << endl;
    return 0;
}