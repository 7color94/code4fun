#include<iostream>
#include<string.h>
#include<queue>

using namespace std;

int edge[505][505];
int a[505];
int path[505];

int findPath(int n) {
	memset(a, 0, sizeof(a));
	a[1] = 2147483647;
	queue<int> q;
	q.push(1);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u == n) return a[n];
		for (int v = 1; v <= n; v++) {
			if (!a[v] && edge[u][v] > 0) {
				path[v] = u;
				a[v] = min(a[u], edge[u][v]);
				q.push(v);
			}
		}
	}
	return 0;
}

int main() {
	int n, m;
	cin >> n >> m;
	int u, v, c;
	memset(edge, 0, sizeof(edge));
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> c;
		edge[u][v] += c;
	}
	int sum = 0;
	while (int flow = findPath(n)) {
		for (int u = n; u != 1; u = path[u]) {
			edge[path[u]][u] -= flow;
			edge[u][path[u]] += flow;
		}
		sum += flow;
	}
	cout << sum << endl;
	system("pause");
}