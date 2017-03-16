#include<iostream>
#include<queue>
#include<set>
#include<fstream>
#include<memory>
#include<limits>
#include<algorithm>
#include<cstring>

using namespace std;

#define MAXN 100005
#define MAXM 1000005

int N, k, u, edgenum, cc;
int first[MAXN], deg[MAXN];
set<int> fathers[MAXN];

struct edge {
	int u;
	int v;
	int next;
}edges[MAXM];

void add_edge(int u, int v) {
	edges[edgenum].u = u;
	edges[edgenum].v = v;
	edges[edgenum].next = first[u];
	first[u] = edgenum++;
	deg[v]++;
}

void bfs() {
	cc = 0;
	queue<int> q;
	for (int i = 0; i <= N; i++) {
		if (deg[i] == 0) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u == 0 || fathers[u].find(0) != fathers[u].end() || fathers[u].size() > 1) {
			if (u != 0) {
				cc++;
			}
			for (int k = first[u]; k != -1; k = edges[k].next) {
				int v = edges[k].v;
				fathers[v].insert(u);
				deg[v]--;
				if (deg[v] == 0) {
					q.push(v);
				}
			}
		} else if (fathers[u].size() == 1) {
			for (int k = first[u]; k != -1; k = edges[k].next) {
				int v = edges[k].v;
				deg[v]--;
				fathers[v].insert(*(fathers[u].begin()));
				if (deg[v] == 0) {
					q.push(v);
				}
			}
		}
	}
}

int main() {
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	cin >> N;
	memset(first, -1, sizeof(first));
	memset(deg, 0, sizeof(deg));
	edgenum = 0;
	for (int i = 1; i <= N; i++) {
		cin >> k;
		while (k--) {
			cin >> u;
			add_edge(u, i);
		}
	}
	bfs();
	cout << cc << endl;
}