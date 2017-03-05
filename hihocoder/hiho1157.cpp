#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int degrees[100005];
vector<int> edges[100005];
int c[100005];

void topu(int N) {
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (degrees[i] == 0) {
            q.push(i);
        }
    }
    while (q.size() != 0) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < edges[u].size(); i++) {
            c[edges[u][i]] += c[u];
            c[edges[u][i]] %= 142857;
            degrees[edges[u][i]]--;
            if (degrees[edges[u][i]] == 0) {
                q.push(edges[u][i]);
            }
        }
    }
}

int main() {
    int N, M, K;
    std::cin >> N >> M >> K;
    int i = 0;
    for (i = 0; i < 100005; i++) {
        degrees[i] = c[i] = 0;
    }
    while (K--) {
        std::cin >> i;
        c[i] = 1;
    }
    while (M--) {
        int u, v;
        std::cin >> u >> v;
        edges[u].push_back(v);
        degrees[v]++;
    }
    topu(N);
    int sum = 0;
    for (int i = 1; i <= N; i++) {
        sum += c[i];
        sum %= 142857;
    }
    std::cout << sum << std::endl;
    return 0;
}
