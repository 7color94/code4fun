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
#include <unordered_map>
using namespace std;

struct edge {
    int u, v, w;
    int next;
} e[500100];

int edgenum;
int first[100010];
int degree[100010];
int T, N, M;
int vis[100010];

void add_edge(int u, int v, int w) {
    e[edgenum].u = u;
    e[edgenum].v = v;
    e[edgenum].w = w;
    e[edgenum].next = first[u];
    first[u] = edgenum++;
    degree[v]++;
}

bool topo() {
    int total = 0;
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    for (int u = 1; u <= N; u++) {
        if (degree[u] == 0 && vis[u] == 0) {
            q.push(u);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 1;
        for (int k = first[u]; k != -1; k = e[k].next) {
            int v = e[k].v;
            degree[v]--;
            if (degree[v] == 0 && vis[v] == 0) q.push(v);
        }
        total++;
    }
    if (total >= N) return true;
    else return false;
}

int main() {
    ifstream cin("in.txt");
    cin >> T;
    while (T--) {
        cin >> N >> M;
        edgenum = 0;
        memset(first, -1, sizeof(first));
        memset(degree, 0, sizeof(degree));
        for (int i = 1; i <= M; i++) {
            int u, v, w;
            cin >> u >> v;
            add_edge(u, v, w);
        }

        bool ok = topo();
        if (ok) cout << "Correct" << endl;
        else cout << "Wrong" << endl;
    }

    return 0;
}