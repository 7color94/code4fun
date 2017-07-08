#include <iostream>
using namespace std;

const int MOD = 1e9 + 7;

long long f[150]; // f[i]: i位二进制数 非法二进制数的个数
long long g[150]; // g[i]: i位二进制数 第i位即末尾为1 的合法二进制数个数
long long h[150]; // h[i]: i位二进制数 第i位即末尾为0 的合法二进制数个数

int main() {
    int n;
    cin >> n;

    f[1] = 0; g[1] = 1; h[1] = 1;
    for (int i = 2; i <= n; i++) {
        f[i] = (f[i - 1] * 2  % MOD + g[i - 1] % MOD) % MOD;
        g[i] = h[i - 1] % MOD;

        long long a = 1;
        for (int j = 1; j <= i; j++) {
            a = (a * 2) % MOD;
        }
        
        h[i] = (a - f[i] % MOD - g[i] % MOD + MOD) % MOD;
    }

    cout << f[n] << endl;
    return 0;
}