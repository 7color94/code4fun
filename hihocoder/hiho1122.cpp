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

int N, M, ans;
int edgenum;
int first[1010];
int visited[1010];
int ok[1010];

struct edge {
	int u, v;
	int next;
}e[10010];

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

bool FindPath(int u) {
	for (int k = first[u]; k != -1; k = e[k].next) {
		int v = e[k].v;
		if (!visited[v]) {
			visited[v] = 1;
			if (ok[v] == -1 || FindPath(ok[v])) {
				ok[u] = v;
				ok[v] = u;
				return true;
			}
		}
	}
	return false;
}

int main() {
	ifstream cin("in.txt");

	cin >> N >> M;
	edgenum = 0;
	memset(first, -1, sizeof(first));
	memset(ok, -1, sizeof(ok));
	int u, v;
	for (int i = 0; i < M; i++) {
		cin >> u >> v;
		addEdge(u, v);
	}
	ans = 0;
	for (int i = 1; i <= N; i++) {
		if (ok[i] == -1) {
			memset(visited, 0, sizeof(visited));
			visited[i] = 1;
			if (FindPath(i)) ans++;
		}
	}
	cout << ans << endl;

	return 0;
}