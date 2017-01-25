#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

vector<int> edges[20005];
stack<int> vertices;
int groups[20005];
int dfn[20005], low[20005], parent[20005], children[20005];
int ord = 0;
int groupnums = 0;

void tarjan(int u) {
    low[u] = dfn[u] = ++ord;
    bool flag = false;
    vertices.push(u);
    for (size_t i = 0; i < edges[u].size(); i++) {
        int v = edges[u][i];
        // 树边/父子边
        if (!dfn[v]) {
            parent[v] = u;
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else {
            if (v != parent[u]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    if (low[u] == dfn[u]) {
        vector<int> grop;
        int minid = 20010;
        while (true) {
            int t = vertices.top();
            grop.push_back(t);
            minid = min(t, minid);
            vertices.pop();
            if (t == u) {
                break;
            }
        }
        groupnums++;
        for (size_t i = 0; i < grop.size(); i++) {
            groups[grop[i]] = minid;
        }
    }
}

int main() {
    int N, M;
    std::cin >> N >> M;
    int u, v;
    while (M--) {
        std::cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    for (int i = 0; i < 20005; i++) {
        dfn[i] = low[i] = parent[i] = children[i] = groups[i]  = 0;
    }
    tarjan(1);
    std::cout << groupnums << std::endl;
    for (int i = 1; i <= N; i++) {
        std::cout << groups[i] << " ";
    }
    return 0;
}
