#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
#include <climits>
#include <random>
#include <queue>
using namespace std;

int N, M;
int S, T;

int edgenum;
int first[510];

int vis[510];
int path[510];
int dis[510];

struct edge {
    int u, v;
    int flow;
    int cap;
    int cost;
    int next;
} e[50000];


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
    int sum = 0;

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
        sum += a;
    }

    return sum;
}

int main() {

    ifstream cin("in.txt");
    cin >> N >> M;
    
    S = 0;
    T = N + M + 1;

    edgenum = 0;
    memset(first, -1, sizeof(first));

    int m;
    for (int i = 1; i <= M; i++) {
        cin >> m;
        addEdge(N + i, T, m);
    }

    int a, k;
    int sum = 0;
    for (int i = 1; i <= N; i++) {
        cin >> a >> k;
        addEdge(S, i, a);
        sum += a;
        int _b;
        while (k--) {
            cin >> _b;
            // cap is inf
            addEdge(i, N + _b, INT16_MAX);
        }
    }
    
    int ans = Edmonds_Karp();
    cout << sum - ans << endl;

    return 0;
}
