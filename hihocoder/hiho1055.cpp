#include<iostream>
#include<vector>
#include <cstring>

using namespace std;

#define MAXN 105

vector<int> graph[MAXN];
int dp[MAXN][MAXN];
int v[MAXN];
int N, M;

void dfs_package(int root) {
    for (int i = 0; i < graph[root].size(); i++) {
        dfs_package(graph[root][i]);
    }
    dp[root][0] = 0;
    dp[root][1] = v[root];
    for (int i = 0; i < graph[root].size(); i++) {
        for (int m = M; m >= 2; m--) {
            for (int m_child = 1; m_child <= m - 1; m_child++) {
                dp[root][m] = max(dp[root][m], dp[root][m-m_child] + dp[graph[root][i]][m_child]);
            }
        }
    }
}

int main() {
    cin >> N >> M;
    memset(v, 0, sizeof(v));
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= N; i++) {
        cin >> v[i];
    }
    int u, v;
    for (int i = 1; i <= N-1; i++) {
        cin >> u >> v;
        if (u < v) {
            graph[u].push_back(v);
        } else {
            graph[v].push_back(u);
        }
    }
    dfs_package(1);
    std::cout << dp[1][M] << std::endl;
    return 0;
}
