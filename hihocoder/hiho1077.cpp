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

struct node {
    int l, r;
    int ans; // save the lowest heavy
    node(): ans(10010){};
} tree[4000010];

int a[1000010];

void build(int index, int l, int r) {
    tree[index].l = l;
    tree[index].r = r;
    if (l == r) {
        tree[index].ans = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * index, l, m);
    build(2 * index + 1, m + 1, r);
    tree[index].ans = min(tree[2 * index].ans, tree[2 * index + 1].ans);
}

void update(int index, int pos, int w) {
    if (tree[index].l == tree[index].r) {
        if (tree[index].l == pos) tree[index].ans = w;
        return;
    }
    int l = tree[index].l;
    int r = tree[index].r;
    int m = (l + r) / 2;
    if (pos <= m) update(index * 2, pos, w);
    else update(index * 2 + 1, pos, w);
    tree[index].ans = min(tree[2 * index].ans, tree[2 * index + 1].ans);
}

int query(int index, int L, int R) {
    if (tree[index].l == L && tree[index].r == R) return tree[index].ans;
    int l = tree[index].l;
    int r = tree[index].r;
    int m = (l + r) / 2;
    if (R <= m) return query(index * 2, L, R);
    else if (L > m) return query(index * 2 + 1, L, R);
    else return min(query(index * 2, L, m), query(index * 2 + 1, m + 1, R));
}

int main() {
    // ifstream cin("in.txt");
    freopen("in.txt", "r", stdin);
    
    int N;
    scanf("%d", &N);
    
    for (int i = 1; i <= N; i++) scanf("%d", &a[i]);
    build(1, 1, N);

    int Q;
    scanf("%d", &Q);
    for (int q = 1; q <= Q; q++) {
        int oo;
        scanf("%d", &oo);
        if (oo == 0) {
            // query
            int L, R;
            scanf("%d %d", &L, &R);
            int ans = query(1, L, R);
            printf("%d\n", ans);
        } else {
            // update
            int pos, w;
            scanf("%d %d", &pos, &w);
            update(1, pos, w);
        }
    }

    return 0;
}