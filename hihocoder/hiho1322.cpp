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
#include <ctime>
#include <cstdlib>
#include <unordered_map>
using namespace std;

struct edge {
    int u, v;
    int next;
} e[300100];

int first[600], vis[600];
int T, N, M;
int edgenum;

void add_edge(int u, int v) {
    e[edgenum].u = u;
    e[edgenum].v = v;
    e[edgenum].next = first[u];
    first[u] = edgenum++;

    e[edgenum].u = v;
    e[edgenum].v = u;
    e[edgenum].next = first[v];
    first[v] = edgenum++;
}

bool is_connect() {
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int k = first[u]; k != -1; k = e[k].next) {
            int v = e[k].v;
            if (vis[v] == 0) {
                q.push(v);
                vis[v] = 1;
            }
        }
    }
    for (int u = 1; u <= N; u++) {
        if (vis[u] == 0) return false;
    }
    return true;
}

int main() {
    // ifstream cin("in.txt");
    // freopen("in.txt", "r", stdin);
    cin >> T;
    while (T--) {
        edgenum = 0;
        memset(first, -1, sizeof(first));
        int a, b;
        cin >> N >> M;
        for (int i = 1; i <= M; i++) {
            cin >> a >> b;
            add_edge(a, b);
        }
        memset(vis, 0, sizeof(vis));
        bool ok = is_connect();
        if (ok && N == M + 1) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}