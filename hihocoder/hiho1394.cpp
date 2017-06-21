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

int N, M;
int edgenum;
int S, T;
int first[1510];
int vis[1510];
int path[1510];
int dis[1510];

struct edge {
    int u, v;
    int flow;
    int cap;
    int cost;
    int next;
}e[50000];

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

int Edmonds_Karp() {
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

    int ans = N;
    for (int i = N + 1; i <= N + N; i++) {
        for (int k = first[i]; k != -1; k = e[k].next) {
            if (e[k].v == T) {
                if (e[k].flow == e[k].cap) ans--;
            }
        }
    }

    return ans;
}

int main() {
    ifstream cin("in.txt");

    cin >> N >> M;
    // A node id: [1, N]
    // B node id: [N + 1, N + N]
    S = 0;
    T = N + N + 1;

    edgenum = 0;
    memset(first, -1, sizeof(first));

    for (int i = 1; i <= N; i++) {
        addEdge(S, i, 1);
        addEdge(N + i, T, 1);
    }
    
    int a, b;
    for (int i = 1; i <= M; i++) {
        cin >> a >> b;
        addEdge(a, N + b, 1);
    }

    int ans = Edmonds_Karp();
    cout << ans << endl;

    return 0;
}