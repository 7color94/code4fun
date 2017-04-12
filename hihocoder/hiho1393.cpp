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

int cases, N, M;
int edgenum;
int S, T;
int first[210];
int vis[210];
int path[210];
int dis[210];

struct edge {
	int u, v;
	int flow;
	int cap;
	int cost;
	int next;
}e[30000];

void addEdge(int u, int v, int cap) {
	e[edgenum].u = u;
	e[edgenum].v = v;
	e[edgenum].flow = 0;
	e[edgenum].cap = cap;
	e[edgenum].cost = 1;
	e[edgenum].next = first[u];
	first[u] = edgenum++;

	e[edgenum].u = v;
	e[edgenum].v = u;
	e[edgenum].flow = 0;
	e[edgenum].cap = 0;
	e[edgenum].cost = -1;
	e[edgenum].next = first[v];
	first[v] = edgenum++;
}

bool Edmonds_Karp() {
	queue<int> q;
	while (true) {
		memset(vis, 0, sizeof(vis));
		memset(path, -1, sizeof(path));
		for (int i = 0; i <= T; i++) {
			dis[i] = (i == 0 ? 0 : INT16_MAX);
		}
		q.push(0);
		vis[0] = 1;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			vis[u] = 0;
			for (int k = first[u]; k != -1; k = e[k].next) {
				int v = e[k].v;
				if (e[k].cap > e[k].flow && dis[v] > dis[u] + e[k].cost) {
					dis[v] = dis[u] + e[k].cost;
					path[v] = k;
					if (0 == vis[v]) {
						q.push(v);
						vis[v] = 1;
					}
				}
			}
		}
		if (dis[T] == INT16_MAX) {
			break;
		}
		int a = INT16_MAX;
		for (int k = path[T]; k != -1; k = path[e[k].u]) {
			a = min(a, e[k].cap - e[k].flow);
		}
		for (int k = path[T]; k != -1; k = path[e[k].u]) {
			e[k].flow += a;
			e[k ^ 1].flow -= a;
		}
	}
	for (int i = N + 1; i <= N + M; i++) {
		for (int k = first[i]; k != -1; k = e[k].next) {
			if (e[k].v == T) {
				if (e[k].flow == e[k].cap) break;
				else return false;
			}
		}
	}
	return true;
}

int main() {
	//ifstream cin("in.txt");
	scanf("%d", &cases);
	while (cases--) {
		scanf("%d %d", &N, &M);
		edgenum = 0;
		S = 0;
		T = N + M + 1;
		memset(first, -1, sizeof(first));
		int m;
		for (int i = 1; i <= M; i++) {
			scanf("%d", &m);
			addEdge(N + i, T, m);
		}
		int a, b;
		for (int i = 1; i <= N; i++) {
			scanf("%d %d", &a, &b);
			addEdge(S, i, a);
			int _b;
			while (b--) {
				scanf("%d", &_b);
				addEdge(i, N + _b, 1);
			}
		}
		if (Edmonds_Karp()) cout << "Yes" << endl;
		else cout << "No" << endl;
	}

	return 0;
}