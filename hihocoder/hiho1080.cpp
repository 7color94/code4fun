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
    int priceSum, lazyTagSet, lazyTagAdd, length;
    node(): priceSum(0), lazyTagSet(-1), lazyTagAdd(0), length(0) {};
} tree[4000010];

int a[100010];

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

void release_tag(int index) {
	if (tree[index].lazyTagSet != -1) {
		tree[2 * index].lazyTagSet = tree[2 * index + 1].lazyTagSet = tree[index].lazyTagSet;
		tree[2 * index].lazyTagAdd = tree[2 * index + 1].lazyTagAdd = 0;

		tree[2 * index].priceSum = tree[2 * index].length * tree[2 * index].lazyTagSet;
		tree[2 * index + 1].priceSum = tree[2 * index + 1].length * tree[2 * index + 1].lazyTagSet;

		tree[index].lazyTagSet = -1;
	}
	if (tree[index].lazyTagAdd != 0) {
		tree[2 * index].lazyTagAdd += tree[index].lazyTagAdd;
		tree[2 * index + 1].lazyTagAdd += tree[index].lazyTagAdd;

		tree[2 * index].priceSum += tree[2 * index].length * tree[index].lazyTagAdd;
		tree[2 * index + 1].priceSum += tree[2 * index + 1].length * tree[index].lazyTagAdd;

		tree[index].lazyTagAdd = 0;
	}
}

void update_tree(int index, int L, int R, int w, int isset) {
    
    if (tree[index].l == L && tree[index].r == R) {
        if (isset) {
            tree[index].lazyTagSet = w;
            tree[index].priceSum = tree[index].length * w;
			tree[index].lazyTagAdd = 0;
        } else {
            tree[index].lazyTagAdd += w;
            tree[index].priceSum += tree[index].length * w;
        }
        return;
    }

	release_tag(index);

    int l = tree[index].l;
    int r = tree[index].r;
    int m = (l + r) / 2;
    if (R <= m) {
        update_tree(index * 2, L, R, w, isset);
    } else if (L > m) {
        update_tree(index * 2 + 1, L, R, w, isset);
    } else {
        update_tree(index * 2, L, m, w, isset);
        update_tree(index * 2 + 1, m + 1, R, w, isset);
    }
    tree[index].priceSum = tree[2 * index].priceSum + tree[2 * index + 1].priceSum;
}

int main() {
    // ifstream cin("in.txt");
    freopen("in.txt", "r", stdin);
    
    int N, M;
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i <= N; i++) scanf("%d", &a[i]);
    build(1, 0, N);

    for (int q = 1; q <= M; q++) {
        int oo, L, R, w;
        scanf("%d %d %d %d", &oo, &L, &R, &w);
        update_tree(1, L, R, w, oo);
        int ans = tree[1].priceSum;
        printf("%d\n", ans);
    }

    return 0;
}