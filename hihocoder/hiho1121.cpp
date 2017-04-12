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

int T, N, M;
int edgenum;
int color[10010];
int first[10010];
struct edge {
	int u, v;
	int next;
}e[80010];

void addEdge(int u, int v) {
	e[edgenum].u = u;
	e[edgenum].v = v;
	e[edgenum].next = first[u];
	first[u] = edgenum++;
	e[edgenum].u = v;
	e[edgenum].v = u;
	e[edgenum].next = first[v];
	first[v] = edgenum++;
}

bool mark(int nodeid) {
	// mark node 1 as white
	if (color[nodeid] == -1) {
		color[nodeid] = 0;
	}
	queue<int> q;
	q.push(nodeid);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int k = first[u]; k != -1; k = e[k].next) {
			if (color[e[k].v] == -1) {
				if (color[u] == 1) color[e[k].v] = 0;
				else color[e[k].v] = 1;
				q.push(e[k].v);
			} else {
				if (color[e[k].v] == color[u]) {
					return false;
				}
			}
		}
	}
	return true;
}

int main() {
	ifstream cin("in.txt");
	cin >> T;
	while (T--) {
		cin >> N >> M;
		edgenum = 0;
		memset(color, -1, sizeof(color));
		memset(first, -1, sizeof(first));
		int u, v;
		for (int i = 0; i < M; i++) {
			cin >> u >> v;
			addEdge(u, v);
		}
		int i = 1;
		for (i = 1; i <= N; i++) {
			if (!mark(i)) break;
		}
		if (i <= N) cout << "Wrong" << endl;
		else cout << "Correct" << endl;
	}
	return 0;
}