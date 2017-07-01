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

int N, M;
int f[20010];
int A[35], B[35];

int main() {
    ifstream cin("in.txt");
    
    cin >> N >> M;
    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));
    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i];
    }

    memset(f, 0, sizeof(f));
    for (int i = 0; i < N; i++) {
        // !!! important, 0/1背包 而非 完全背包
        for (int v = M; v >= 0; v--) {
            for (int x = 1; ; x++) {
                int base = B[i], cost = B[i];
                for (int iter = 1; iter < x; iter++) {
                    base = int(1.07 * base);
                    cost += base;
                }
                if (cost > v) break;
                f[v] = max(f[v], f[v - cost] + A[i] * x);
            }
        }
    }

    int ans = 0;
    for (int v = 0; v <= M; v++) {
        if (f[v] > ans) ans = f[v];
    }

    cout << ans << endl;

    return 0;
}