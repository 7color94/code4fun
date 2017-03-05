#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Edge {
    int u, v, id;
};

const int M = 100000;
const int N = 20000;
Edge edge[2 * M + 1];
int next_edge[2 * M + 1];
int to[N + 1];
int dfn[N + 1];
int low[N + 1];
bool visitedEdge[M + 1];
int parent[N + 1];
Edge stacks[M + 1];
int topStack[M + 1];
int top = 0;
int numGroup = 0;
int ord = 0;

void popStack(Edge s) {
    ++numGroup;
    int minNum = s.id;
    int tmpTop = top;
    while (stacks[--tmpTop].id != s.id) {
        minNum = min(stacks[tmpTop].id , minNum);
    }
    while (stacks[--top].id != s.id) {
        topStack[stacks[top].id] = minNum;
    }
    topStack[s.id] = minNum;
}

void tarjan(int u) {
    int children = 0;
    low[u] = dfn[u] = ++ord;
    for (int i = to[u]; i != 0; i = next_edge[i]) {
        if (visitedEdge[edge[i].id]) {
            continue;
        }
        stacks[top++] = edge[i];
        visitedEdge[edge[i].id] = true;
        if (!dfn[edge[i].v]) {
            ++children;
            parent[edge[i].v] = u;
            tarjan(edge[i].v);
            low[u] = min(low[u], low[edge[i].v]);
            if (children > 1 && parent[u] == 0) {
                popStack((edge[i]));
            }
            if (parent[u] != 0 && dfn[u] <= low[edge[i].v]) {
                popStack(edge[i]);
            }
        } else {
            low[u] = min(low[u], dfn[edge[i].v]);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    int e = 0;
    for (int i = 1; i <= m; i++) {
        int u, v;
        std::cin >> u >> v;
        edge[++e].u = u;
        edge[e].v = v;
        edge[e].id = i;
        next_edge[e] = to[u];
        to[u] = e;
        edge[++e].u = v;
        edge[e].v = u;
        edge[e].id = i;
        next_edge[e] = to[v];
        to[v] = e;
    }
    tarjan(1);
    if (top) {
        popStack(edge[to[1]]);
    }
    std::cout << numGroup << std::endl;
    for (int i = 1; i <= m; i++) {
        std::cout << topStack[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
