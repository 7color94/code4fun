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

// Problem: https://nanti.jisuanke.com/t/15969

#define MAXN 60010
#define MAXE 5000000

struct edge {
    int u, v, c;
    int next;
} edges[MAXE];

int first[MAXN];
int edgenum;

int64_t dis[MAXN];
int inqueue[MAXN];

int n, m;

void addEdges(int u, int v, int c) {
    edges[edgenum].u = u;
    edges[edgenum].v = v;
    edges[edgenum].c = c;
    edges[edgenum].next = first[u];
    first[u] = edgenum++;
}


int64_t SPFA(int s, int t) {
    fill(dis, dis + MAXN, INT64_MAX);
    memset(inqueue, 0, sizeof(inqueue));
    dis[s] = 0;
    queue<int> Q;
    Q.push(s);
    inqueue[s] = 1;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        inqueue[u] = 0;
        for (int k = first[u]; k != -1; k = edges[k].next) {
            int v = edges[k].v;
            if (dis[u] + edges[k].c < dis[v]) {
                dis[v] = dis[u] + edges[k].c;
                if (inqueue[v] == 0) {
                    Q.push(v);
                    inqueue[v] = 1;
                }
            }
        }
    }
    if (dis[t] == INT64_MAX) return -1;
    else return dis[t];
}


int main() {

    ifstream cin("in.txt");
    cin >> n >> m;

    memset(first, -1, sizeof(first));
    edgenum = 0;

    int vn = n + 1;

    // input cityGroups
    int k;
    for (int i = 0; i < m; i++) {
        cin >> k;

        int id;
        for (int kk = 0; kk < k; kk++) {
            cin >> id;
            // first
            addEdges(id, vn, 0);
            // second
            addEdges(vn + 1, id, 0);
        }
        vn = vn + 2;
    }
    vn--;

    // input paths between citys
    int m1;
    cin >> m1;
    int u, v, c;
    for (int i = 0; i < m1; i++) {
        cin >> u >> v >> c;
        addEdges(u, v, c);
        addEdges(v, u, c);
    }

    // input paths between cityGroups
    int m2;
    cin >> m2;
    int a, b, l;
    for (int i = 0; i < m2; i++) {
        cin >> a >> b >> l;
        int a_first = n + a * 2 - 1, a_second = n + a * 2;
        int b_first = n + b * 2 - 1, b_second = n + b * 2;
        addEdges(a_first, b_second, l);
        addEdges(b_first, a_second, l);
    }

    // input query
    int s, t;
    cin >> s >> t;
    int64_t ans = SPFA(s, t);

    cout << ans << endl;

    return 0;
}
