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
} e[1000010];


int edgenum;
int first[100010];
int pre[100010];
int N, M;
int heap_size;
int vis[100010];

void add_edge(int u, int v, int w) {
    e[edgenum].u = u;
    e[edgenum].v = v;
    e[edgenum].w = w;
    e[edgenum].next = first[u];
    first[u] = edgenum++;
}

int cmp(edge e1, edge e2) {
    return e1.w < e2.w;
}

int find(int i){
    while (pre[i] != i) {
        pre[i] = pre[pre[i]];
        i = pre[i];
    }
    return i;
}

int kruscal() {
    for (int i = 1; i <= N; i++) pre[i] = i;
    memset(vis, 0, sizeof(vis));
    vis[1] = 1;
    int num = 1;
    int ans = 0;
    for (int i = 0; i < edgenum; i++) {
        int uu = e[i].u;
        int vv = e[i].v;

        int root1 = find(uu);
        int root2 = find(vv);
        if (root1 == root2) continue;
        else pre[root1] = root2;

        ans += e[i].w;
    }
    return ans;
}


int main() {
    ifstream cin("in.txt");
    
    cin >> N >> M;
    edgenum = 0;
    memset(first, -1, sizeof(first));
    for (int i = 1; i <= M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    sort(e, e + edgenum, cmp);

    int ans = kruscal();
    cout << ans << endl;

    return 0;
}