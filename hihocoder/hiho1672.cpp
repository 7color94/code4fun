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
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <stack>
using namespace std;

const int maxn = 1e5 + 5;
const int maxm = 1e6 + 5;

struct Seq {
    int l, r;
    bool operator < (const Seq& rhs) const {
        if (r != rhs.r) return r < rhs.r;
        else return l > rhs.l;
    }
} seqs[maxn];
int bit[maxm];
int in[maxm];

int lowbit(int x) {
    return x & (-x);
}
void add(int x) {
    while (x < maxm) {
        bit[x]++;
        x += lowbit(x);
    }
}
int sum(int x) {
    int ret = 0;
    while(x > 0) {
        ret += bit[x];
        x -= lowbit(x);
    }
    return ret;
}
int main() {
    freopen("in.txt", "r", stdin);
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d %d", &seqs[i].l, &seqs[i].r);
    sort(seqs, seqs + N);
    for (int i = 0; i < N; i++) {
        int j = seqs[i].r;
        while ((sum(seqs[i].r) - sum(seqs[i].l - 1)) < 2) {
            while (in[j]) j--;
            in[j] = 1;
            add(j);
        }
    }
    printf("%d\n", (sum(1e6) - sum(1)));
}