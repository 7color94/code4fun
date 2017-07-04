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

struct edge {
    int u, v;
    int next;
} e[300100];

int T;
int N, M;
int edgenum;
int first[600];
int vis[600];

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

bool dfs(int father, int u) {
    vis[u] = 1;
    bool ok = true;
    for (int k = first[u]; k != -1; k = e[k].next) {
        int v = e[k].v;
        if (vis[v] == 1 && v != father) {
            ok = false;
            break;
        }
        if (vis[v] == 0) {
            if(dfs(u, v) == false) {
                ok = false;
                break;
            }
        }
    }
    return ok;
}

int color[600];
int cc;

void dfs_color(int u, int _cc) {
    color[u] = _cc;
    for (int k = first[u]; k != -1; k = e[k].next) {
        int v = e[k].v;
        if (color[v] != 0) continue;
        dfs_color(v, _cc);
    }
}

int main() {
    ifstream cin("in.txt");
    // freopen("in.txt", "r", stdin);
    
    cin >> T;
    while (T--) {
        cin >> N >> M;

        int a, b;
        edgenum = 0;
        memset(first, -1, sizeof(first));
        for (int i = 1; i <= M; i++) {
            cin >> a >> b;
            add_edge(a, b);
        }

        memset(vis, 0, sizeof(vis));
        bool ok = true;
        for (int u = 1; u <= N; u++) {
            vis[u] = 1;
            for (int k = first[u]; k != -1; k = e[k].next) {
                int v = e[k].v;
                if (vis[v] == 1) continue;
                if (dfs(u, v) == false) {
                    ok = false;
                    break;
                }
            }
            if (ok == false) break;
        }

        if (ok) {
            // for union find
            cc = 0;
            memset(color, 0, sizeof(color));
            for (int u = 1; u <= N; u++) {
                if (color[u] == 0) color[u] = ++cc;
                for (int k = first[u]; k != -1; k = e[k].next) {
                    int v = e[k].v;
                    if (color[v] != 0) continue;
                    dfs_color(v, color[u]);
                }
            }
        }

        if (ok == true && cc == 1) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    return 0;
}