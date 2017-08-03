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
#include <unordered_map>
using namespace std;

int w[1010];
int dp[1010][(1<<10)+10];

int count_ones(int number) {
    int ans = 0;
    while (number) {
        ans += (number&1);
        number = number >> 1;
    }
    return ans;
}

int main() {
    ifstream cin("in.txt");
    // freopen("in.txt", "r", stdin);
    int N, M, Q;
    cin >> N >> M >> Q;
    for (int i = 0; i < N; i++) cin >> w[i];
    memset(dp, 0, sizeof(dp));
    dp[0][1] = w[0];
    for (int i = 1; i < N; i++) {
        for (int s = 0; s < (1<<min(M,i+1)); s++) {
            if (count_ones(s) > Q) continue;
            if (s&1) dp[i][s] = max(dp[i-1][s>>1], dp[i-1][(s>>1)+(1<<(M-1))]) + w[i];
            else dp[i][s] = max(dp[i-1][s>>1], dp[i-1][(s>>1)+(1<<(M-1))]);
        }
    }
    int ans = 0;
    for (int s = 0; s < (1<<min(N,M)); s++) ans = max(ans, dp[N-1][s]);
    cout << ans << endl;
    return 0;
}