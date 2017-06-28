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
#include <unordered_map>
using namespace std;

int a[100020];
int b[100020];

int main() {
    ifstream cin("in.txt");
    
    int T, n, m;
    cin >> T;
    while (T--) {
        cin >> n >> m;

        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));

        unordered_map<int, long long> count_a, count_b;
        int x, y;
        for (int i = 0; i < n; i++) {
            cin >> x >> y;
            count_a[x] += y;
            a[i] = x;
        }

        for (int i = 0; i < m; i++) {
            cin >> x >> y;
            count_b[x] += y;
            b[i] = x;
        }

        sort(a, a + n);
        sort(b, b + m);

        int nn = unique(a, a + n) - a;
        int mm = unique(b, b + m) - b;

        int i = 0, j = 0;
        long long ans = 0, remain = 0;
        for (int i = 0; i < nn; i++) {
            while (j < mm) {
                if (b[j] >= a[i]) break;
                remain += count_b[b[j]];
                j++;
            }
            ans += (remain * count_a[a[i]]);
        }

        cout << ans << endl;
    }

    return 0;
}