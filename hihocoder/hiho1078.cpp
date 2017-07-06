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
    int priceSum, lazyTag, length;
    node(): priceSum(0), lazyTag(-1), length(0) {};
} tree[4000010];

int a[1000010];

void build(int index, int l, int r) {
    tree[index].l = l;
    tree[index].r = r;
    if (l == r) {
        tree[index].length = 1;
        tree[index].priceSum = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * index, l, m);
    build(2 * index + 1, m + 1, r);
    tree[index].length = tree[2 * index].length + tree[2 * index + 1].length;
    tree[index].priceSum = tree[2 * index].priceSum + tree[2 * index + 1].priceSum;
}

void update(int index, int L, int R, int w) {
    if (tree[index].l == L && tree[index].r == R) {
        tree[index].lazyTag = w;
        tree[index].priceSum = tree[index].length * tree[index].lazyTag;
        return;
    }
    // check lazyTag
    if (tree[index].lazyTag != -1) {
        tree[2 * index].lazyTag = tree[index].lazyTag;
        tree[2 * index].priceSum = tree[2 * index].lazyTag * tree[2 * index].length;

        tree[2 * index + 1].lazyTag = tree[index].lazyTag;
        tree[2 * index + 1].priceSum = tree[2 * index + 1].lazyTag * tree[2 * index + 1].length;

        tree[index].lazyTag = -1;
    }
    int l = tree[index].l;
    int r = tree[index].r;
    int m = (l + r) / 2;
    if (R <= m) {
        update(index * 2, L, R, w);
    }
    else if (L > m) {
        update(index * 2 + 1, L, R, w);
    }
    else {
        update(index * 2, L, m, w);
        update(index * 2 + 1, m + 1, R, w);
    }
    tree[index].priceSum = tree[2 * index].priceSum + tree[2 * index + 1].priceSum;
}

int query(int index, int L, int R) {
    if (tree[index].l == L && tree[index].r == R) return tree[index].priceSum;
    // check lazyTag
    if (tree[index].lazyTag != -1) {
        tree[2 * index].lazyTag = tree[index].lazyTag;
        tree[2 * index].priceSum = tree[2 * index].lazyTag * tree[2 * index].length;

        tree[2 * index + 1].lazyTag = tree[index].lazyTag;
        tree[2 * index + 1].priceSum = tree[2 * index + 1].lazyTag * tree[2 * index + 1].length;

        tree[index].lazyTag = -1;
    }
    int l = tree[index].l;
    int r = tree[index].r;
    int m = (l + r) / 2;
    if (R <= m) return query(index * 2, L, R);
    else if (L > m) return query(index * 2 + 1, L, R);
    else return query(index * 2, L, m) + query(index * 2 + 1, m + 1, R);
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
        int oo, L, R, w;
        scanf("%d", &oo);
        if (oo == 0) {
            // query
            scanf("%d %d", &L, &R);
            int ans = query(1, L, R);
            printf("%d\n", ans);
        } else {
            // update
            scanf("%d %d %d", &L, &R, &w);
            update(1, L, R, w);
        }
    }

    return 0;
}