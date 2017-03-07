#include<stdio.h>
#include<queue>
#include<algorithm>
#include<limits>

using namespace std;

const int MAXN = 105;

int edges[MAXN][MAXN];
int a[MAXN];
int path[MAXN];
int n, np, nc, m;

int Edmonds_Karp(int s, int t) {
	queue<int> q;
	int ans = 0;
	while (true) {
		memset(a, 0, sizeof(a));
		a[s] = INT_MAX;
		q.push(s);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int v = 0; v <= n + 1; v++) {
				if (!a[v] && edges[u][v]) {
					a[v] = min(a[u], edges[u][v]);
					path[v] = u;
					q.push(v);
				}
			}
		}
		if (a[t] == 0) {
			break;
		}
		int v = t;
		for (int u = t; u != s; u = path[u]) {
			edges[path[u]][u] -= a[t];
			edges[u][path[u]] += a[t];
		}
		ans += a[t];
	}
	return ans;
}

int main() {
	while (scanf("%d %d %d %d", &n, &np, &nc, &m) != EOF) {
		int u, v, w;
		memset(edges, 0, sizeof(edges));
		for (int i = 0; i < m; i++) {
			scanf(" (%d,%d)%d", &u, &v, &w);
			edges[u + 1][v + 1] += w;
		}
		for (int i = 0; i < np; i++) {
			scanf(" (%d)%d", &u, &w);
			edges[0][u + 1] += w;
		}
		for (int i = 0; i < nc; i++) {
			scanf(" (%d)%d", &u, &w);
			edges[u + 1][n + 1] += w;
		}
		printf("%d\n", Edmonds_Karp(0, n + 1));
	}
}