#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

const int maxn = 1e5 + 5;
const int maxm = 2e5 + 5;

int edgenum, n, ans;
int A[maxn];
int first[maxn];
map<int, int> dp[maxn];

struct edge {
    int u, v;
    int next;
} e[maxm];

void addEdge(int u, int v) {
    e[edgenum].u = u;
    e[edgenum].v = v;
    e[edgenum].next = first[u];
    first[u] = edgenum++;
    e[edgenum].u = v;
    e[edgenum].v = u;
    e[edgenum].next = first[v];
    first[v] = edgenum++;
}

void dfs(int u, int father) {
    for (int k = first[u]; k != -1; k = e[k].next) {
        int v = e[k].v;
        if (v != father) {
            dfs(v, u);
            int cha = A[v] - A[u];
            if (cha == 0) {
                ans = max(ans, dp[u][cha]+dp[v][cha]+2);
                dp[u][cha] = max(dp[u][cha], dp[v][cha] + 1);
            } else {
                dp[u][cha] = max(dp[u][cha], dp[v][cha] + 1);
                ans = max(ans, dp[u][cha]+dp[u][-cha]+1);
            }
        }
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    memset(A, 0, sizeof(A));
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
    int u, v;
    edgenum = 0;
    memset(first, -1, sizeof(first));
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    ans = 0;
    dfs(1, -1);
    printf("%d\n", ans);
    return 0;
}
