#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
using namespace std;

int N, M, Q;
int X, Y, S;

struct edge {
	int u;
	int v;
	int score;
	int next;
}e[200010];

int edgenum;
int first[100010];

int vis[100010];
int mark[100010];
int dis[100010];

int id[100010];

void add_edge(int u, int v, int score) {
	e[edgenum].u = u;
	e[edgenum].v = v;
	e[edgenum].score = score;
	e[edgenum].next = first[u];
	first[u] = edgenum++;
	e[edgenum].u = v;
	e[edgenum].v = u;
	e[edgenum].score = -score;
	e[edgenum].next = first[v];
	first[v] = edgenum++;
	// unions(u, v);
}

void bfs(int u) {
	memset(vis, 0, sizeof(vis));
	queue<pair<int,int>> q;
	q.push(make_pair(u, 0));
	dis[u] = 0;
	mark[u] = 1;
	id[u] = u;
	while (!q.empty()) {
		pair<int, int> pp = q.front();
		q.pop();
		int uu = pp.first;
		int dd = pp.second;
		for (int k = first[uu]; k != -1; k = e[k].next) {
			int v = e[k].v;
			dis[v] = dd + e[k].score;
			id[v] = u;
			if (mark[v] == 0) {
				q.push(make_pair(v, dd + e[k].score));
			}
			mark[v] = 1;
		}
	}
}

void build() {
	memset(dis, -1, sizeof(dis));
	for (int u = 1; u <= N; u++) {
		if (!mark[u]) bfs(u);
	}
}

int main() {
	ifstream cin("in.txt");
	cin >> N >> M >> Q;

	edgenum = 0;
	memset(first, -1, sizeof(first));
	for (int i = 1; i <= N; i++) id[i] = i;

	for (int i = 0; i < M; i++) {
		cin >> X >> Y >> S;
		add_edge(X, Y, S);
	}

	build();

	for (int i = 0; i < Q; i++) {
		cin >> X >> Y;
		if (id[X] == id[Y]) cout << -dis[X] + dis[Y] << endl;
		else cout << -1 << endl;
	}

	return 0;
}