#include<iostream>
#include<fstream>
#include<queue>
#include<limits>

using namespace std;

struct edge {
	int u;
	int v;
	long long cost;
	int flow;
	int cap;
	int next;
}e[10005];

int first[1005];
int dis[1005];
int vis[1005];
int path[10005];
int edgenum;
int n, m;

void add_edge(int u, int v, int cost, int cap) {
	e[edgenum].u = u;
	e[edgenum].v = v;
	e[edgenum].cost = cost;
	e[edgenum].flow = 0;
	e[edgenum].cap = cap;
	e[edgenum].next = first[u];
	first[u] = edgenum++;
	e[edgenum].u = v;
	e[edgenum].v = u;
	e[edgenum].cost = -cost;
	e[edgenum].flow = 0;
	e[edgenum].cap = 0;
	e[edgenum].next = first[v];
	first[v] = edgenum++;
}

int EK() {
	queue<int> q;
	int ans = 0;
	while (true) {
		memset(vis, 0, sizeof(vis));
		memset(path, -1, sizeof(path));
		for (int i = 0; i <= n + 1; i++) {
			dis[i] = (i == 0 ? 0 : INT_MAX);
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
		if (dis[n + 1] == INT_MAX) {
			break;
		}
		int a = INT_MAX;
		for (int k = path[n + 1]; k != -1; k = path[e[k].u]) {
			a = min(a, e[k].cap - e[k].flow);
		}
		for (int k = path[n + 1]; k != -1; k = path[e[k].u]) {
			e[k].flow += a;
			e[k ^ 1].flow -= a;
		}
		ans += dis[n + 1] * a;
	}
	return ans;
}

int main() {
	//ifstream cin("input.txt");
	//ofstream cout("output.txt");
	//cin >> n;
	//cin >> m;
	while (scanf("%d %d", &n, &m) != EOF) {
		int u, v, cost;
		edgenum = 0;
		memset(first, -1, sizeof(first));
		for (int i = 0; i < m; i++) {
			//cin >> u >> v >> cost;
			scanf("%d %d %d", &u, &v, &cost);
			add_edge(u, v, cost, 1);
			add_edge(v, u, cost, 1);
		}
		add_edge(0, 1, 0, 2);
		add_edge(n, n + 1, 0, 2);
		int ans = EK();
		//cout << ans << endl;
		printf("%d\n", ans);
		return 0;
	}
	
}