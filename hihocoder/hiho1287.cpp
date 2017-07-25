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

long long multi_mod(long long a, long long b, long long mo) {
    long long ans = 0;
    while(b) {
        if (b&1) ans = (ans + a) % mo;
        a = (a <<= 1) % mo;
        b >>=1 ;
    }
    return ans;
}

long long pow_mod(long long x, long long y, long long mo) {
    long long ans = 1, base = x;
    while (y) {
        if (y & 1) ans = multi_mod(ans, base, mo);
        base = multi_mod(base, base, mo);
        y >>= 1;
    }
    return ans;
}

bool Miller_Rabin(long long n) {
    if (n <= 2) {
        if (n == 2) return true;
        else return false;
    }
    if (n % 2 == 0) return false;
    long long u = n - 1;
    while (u % 2 == 0) u = u / 2;
    cout << u << endl;
    for (int iters = 0; iters < 20; iters++) {
        // [2, n-1]
        long long a = rand() % (n-1 - 2 + 1) + 2;
        long long x = pow_mod(a, u, n);
        while (u < n) {
            long long y = pow_mod(x, 2, n);
            if (y == 1 && x != 1 && x != n - 1) return false;
            x = y;
            u = u * 2;
        }
        if (x != 1) return false;
    }
    return true;
}

int main() {
    ifstream cin("in.txt");
    // freopen("in.txt", "r", stdin);
    
    srand(time(NULL));
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        if (Miller_Rabin(n)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }

    return 0;
}