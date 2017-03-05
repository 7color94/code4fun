#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

vector<int> edges[20005];
int w[20005];
int dfn[20005];
int low[20005];
stack<int> vertices;
int ord;
bool visited[20005];
int id[20005];
int sum;
int ans;

void tarjan(int u) {
    low[u] = dfn[u] = ++ord;
    vertices.push(u);
    visited[u] = true;
    for (int i = 0; i < edges[u].size(); i++) {
        int v = edges[u][i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (visited[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        int sum = 0;
        while (true) {
            int v = vertices.top();
            vertices.pop();
            visited[v] = false;
            id[v] = u;
            sum += w[v];
            if (v == u) {
                break;
            }
        }
        w[u] = sum;
    }
}

void rebuild(int N) {
    for (int i = 1; i <= N; i++) {
        if (id[i] != i) {
            for (int j = 0; j < edges[i].size(); j++) {
                int c = edges[i][j];
                if (c != id[i]) {
                    edges[id[i]].push_back(c);
                }
            }
        }
    }
}

void dfs(int u) {
    //std::cout << "." << std::endl;
    sum += w[u];
    for (int i = 0; i < edges[u].size(); i++) {
        int v = edges[u][i];
        if (id[v] == u) {
            continue;
        }
        dfs(id[v]);
    }
    ans = max(ans, sum);
    sum -= w[u];
}

int main() {
    int N, M;
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        std::cin >> w[i];
    }
    while (M--) {
        int u, v;
        std::cin >> u >> v;
        edges[u].push_back(v);
    }
    for (int i = 1; i <= N; i++) {
        visited[i] = false;
        id[i] = i;
        dfn[i] = low[i] = 0;
    }
    ord = 0;
    tarjan(1);

    rebuild(N);

    ans = sum = 0;
    dfs(1);

    std::cout << ans << std::endl;
    return 0;
}
