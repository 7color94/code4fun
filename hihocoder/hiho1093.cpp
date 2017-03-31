#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<stack>
#include<queue>

using namespace std;

#define MAXN 100005
#define INF 0x7fffffff

struct edge {
	int y, w;
	edge(int _y, int _w) :y(_y), w(_w) {}
};

vector<edge> v[MAXN];
int d[MAXN], n, m, s, t;
bool inq[MAXN];

void spfa() {
	for (int i = 1; i <= n; ++i) {
		d[i] = INF;
	}
	d[s] = 0;
	memset(inq + 1, 0, n);
	queue<int> q;
	q.push(s);
	inq[s] = true;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		inq[x] = false;
		int sz = v[x].size();
		for (int i = 0; i<sz; ++i) {
			int y = v[x][i].y, w = v[x][i].w;
			if (d[y] > d[x] + w) {
				d[y] = d[x] + w;
				if (!inq[y]) {
					q.push(y);
				}
			}
		}
	}
}

int main() {
	while (cin >> n >> m >> s >> t) {
		for (int i = 1; i <= n; ++i) v[i].clear();
		while (m--) {
			int x, y, w;
			cin >> x >> y >> w;
			v[x].push_back(edge(y, w));
			v[y].push_back(edge(x, w));
		}
		spfa();
		cout << d[t] << endl;
	}
	return 0;
}