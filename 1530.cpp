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
using namespace std;

long long pow_mod(long long x, long long y, long long mo) {
    long long ans = 1, base = x;
    while (y) {
        if (y & 1) ans = ans * base % mo;
        base = base * base % mo;
        y >>= 1;
    }
    return ans;
}

int main() {
    ifstream cin("in.txt");
    // freopen("in.txt", "r", stdin);
    
    long long a, b, p;
    cin >> a >> b >> p;
    long long ans = 0;
    long p_ans = pow_mod(b, p - 2, p);
    ans = ((a % p) * (p_ans % p)) % p;

    cout << ans << endl;

    return 0;
}