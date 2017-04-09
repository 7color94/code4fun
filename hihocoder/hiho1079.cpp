#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

int tree[4000005];
int num[100010];
map<int, int> mp;
int N, L;
set<int> posts;

struct node {
	int x;
	int y;
};
node a[100010];

// index: 线段树节点id
// L, R: 当前节点index表示的区间
// l, r: 需要更新的区间
// x: 需要更新的内容
void UpdateTree(int index, int L, int R, int l, int r, int x) {
	if (r <= L || l >= R) {
		return;
	}
	if (L >= l && R <= r) {
		tree[index] = x;
		return;
	}
	if (tree[index] != 0) {
		if (L + 1 != R) {
			tree[index * 2] = tree[index * 2 + 1] = tree[index];
		}
		tree[index] = 0;
	}
	UpdateTree(index*2, L, (L + R) / 2, l, r, x);
	UpdateTree(index*2+1, (L + R) / 2, R, l, r, x);
}

void Query(int index, int L, int R) {
	if (tree[index] != 0) {
		posts.insert(tree[index]);
		return;
	}
	if (L + 1 != R && tree[index] == 0) {
		Query(index*2, L, (L + R) / 2);
		Query(index * 2 + 1, (L + R) / 2, R);
	}
}

int main() {
	scanf("%d %d", &N, &L);
	int cc = 0;
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &a[i].x, &a[i].y);
		num[cc++] = a[i].x;
		num[cc++] = a[i].y;
	}
	sort(num, num + cc);
	int all = unique(num, num + cc) - num;
	int c = 1;
	for (int i = 0; i < all; i++) {
		mp[num[i]] = c;
		c++;
	}
	memset(tree, 0, sizeof(tree));
	for (int i = 1; i <= N; i++) {
		UpdateTree(1, 1, all, mp[a[i].x], mp[a[i].y], i);
	}
	posts.clear();
	Query(1, 1, all);
	cout << posts.size() << endl;
	
	return 0;
}