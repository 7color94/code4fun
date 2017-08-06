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

int n, m;
int a[100010], b[100010];
int k[1010], p[1010];
int f[1010][20];
int g[1010][20];

int main() {
    // ifstream cin("in.txt");
	// ofstream cout("out.txt");
	// freopen("in.txt", "r", stdin);
	while (scanf("%d %d", &n, &m) != EOF) {
		for (int i = 1; i <= n; i++) scanf("%d %d", &a[i], &b[i]);
		for (int j = 1; j <= m; j++) scanf("%d %d", &k[j], &p[j]);
		fill_n(g[0], 1010 * 20, INT_MAX);
		for (int t = 0; t <= 10; t++) g[0][t] = 0;
		// j: 攻击方案
		for (int j = 1; j <= m; j++) {
			fill_n(f[0], 1010 * 20, INT_MAX);
			for (int t = 0; t <= 10; t++) f[0][t] = 0;
			// q: 生命值
			for (int q = 1; q <= 1000; q++) {
				// t: 防御值
				for (int t = 0; t <= 10; t++) {
					f[q][t] = min(f[q][t], g[q][t]);
					int loss = p[j] - t;
					if (loss <= 0) continue;
					int left = max(0, q - loss);
					f[q][t] = min(f[q][t], f[left][t] + k[j]);
				}
			}
			for (int t = 0; t <= 10; t++) {
				for (int q = 1; q <= 1000; q++) g[q][t] = f[q][t];
			}
		}
		long long ans = 0;
		for (int i = 1; i <= n; i++) {
			if (f[a[i]][b[i]] == INT_MAX) {
				ans = -1;
				break;
			}
			ans += f[a[i]][b[i]];
		}
		printf("%I64d\n", ans);
		//system("pause");
	}
    return 0;
}