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

// https://maskray.me/blog/2013-08-27-josephus-problem-two-log-n-solutions

int Josephus(int n, int k) {
    if (n == 1) return 0;
    if (n < k) {
        int ret = 0;
        for (int i = 2; i <= n; i++) ret = (ret + k) % i;
        return ret;
    }
    int ret = Josephus(n - n / k, k);
    if (ret < (n % k)) ret = ret - n % k + n;
    else ret = ret - n % k + (ret - n % k) / (k - 1);
    return ret;
}

int main() {
    ifstream cin("in.txt");
    // freopen("in.txt", "r", stdin);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int ans = Josephus(n, k);
        cout << ans << endl;
    }

    return 0;
}