#include<iostream>
#include<string.h>
#include<queue>

using namespace std;

struct node{
	int sum;
	int lsum;
	int rsum;
	int multis;
	node(): sum(0), lsum(0), rsum(0), multis(0) {};
};

vector<node> arrays;

void update(int N, int x) {
	arrays[N].lsum = arrays[N].rsum = arrays[N].multis = arrays[N].sum = x % 10007;
	N = N >> 1;
	while (N >= 1) {
		arrays[N].sum = (arrays[N * 2].sum + arrays[N * 2 + 1].sum + arrays[N * 2].rsum * arrays[N * 2 + 1].lsum) % 10007;
		arrays[N].lsum = (arrays[N * 2].lsum + arrays[N * 2 + 1].lsum * arrays[N * 2].multis) % 10007;
		arrays[N].rsum = (arrays[N * 2].rsum * arrays[N * 2 + 1].multis + arrays[N * 2 + 1].rsum) % 10007;
		arrays[N].multis = (arrays[N * 2 + 1].multis * arrays[N * 2].multis) % 10007;
		N = N >> 1;
	}
}

int main() {
	int n, q;
	//cin >> n >> q;
	scanf("%d %d", &n, &q);
	int c = 1;
	while ((1 << c) < n) {
		c++;
	}
	arrays.resize(1 << (c+1));
	int i, x;
	for (int t = 1; t <= q; t++) {
		//cin >> i >> x;
		scanf("%d %d", &i, &x);
		int N = (1 << c) - 1 + i;
		update(N, x);
		//std::cout << arrays[1].sum << std::endl;
		printf("%d\n", arrays[1].sum);
	}
	//system("pause");
}