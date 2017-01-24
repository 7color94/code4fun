#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> edges[20005];
vector<int> cutPoints;
vector<pair<int,int>> cutEdges;
int dfn[20005], low[20005], parent[20005], children[20005];
int ord = 0;

void tarjan(unsigned u) {
    low[u] = dfn[u] = ++ord;
    bool flag = false;
    for (size_t i = 0; i < edges[u].size(); i++) {
        unsigned v = edges[u][i];
        // 树边/父子边
        if (!dfn[v]) {
            parent[v] = u;
            children[u]++;
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                flag = true;
            }
            if (low[v] > dfn[u]) {
                cutEdges.push_back(make_pair(min(u,v), max(u,v)));
            }
        } else {
            if (v != parent[u]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    // 前面情况是根节点, 后面是非根非叶子节点
    if ((parent[u] == 0 && children[u] > 1) || (flag && parent[u])) {
        cutPoints.push_back(u);
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
        dfn[i] = low[i] = parent[i] = children[i] = 0;
    }
    tarjan(1);
    sort(cutPoints.begin(), cutPoints.end());
    sort(cutEdges.begin(), cutEdges.end());
    if (cutPoints.size() == 0) {
        std::cout << "Null" << std::endl;
    } else {
        std::cout << cutPoints[0];
        for (size_t i = 1; i < cutPoints.size(); i++) {
            std::cout << " " << cutPoints[i];
        }
        std::cout << std::endl;
    }
    for (size_t i = 0; i < cutEdges.size(); i++) {
        std::cout << cutEdges[i].first << " " << cutEdges[i].second << std::endl;
    }
    return 0;
}
