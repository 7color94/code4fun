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

int T, B, N;
int score[110], cost[110];

struct state {
	int best, idsum, from, selected;
} dp[110][1010];

int main() {
	// ifstream cin("in.txt");
	// ofstream cout("out.txt");
	// freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int cases = 1; cases <= T; cases++) {
		scanf("%d", &B);
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) scanf("%d %d", &score[i], &cost[i]);
		for (int i = 0; i <= N; i++) {
			for (int v = 0; v <= B; v++) dp[i][v].best = dp[i][v].idsum = dp[i][v].from = dp[i][v].selected = 0;
		}
		for (int i = 1; i <= N; i++) {
			for (int v = 0; v <= B; v++) {
				// no select #i
				dp[i][v].best = dp[i - 1][v].best;
				dp[i][v].idsum = dp[i - 1][v].idsum;
				dp[i][v].from = v;
				dp[i][v].selected = 0;
				// select #i
				if (v - cost[i] >= 0) {
					int tt = dp[i - 1][v - cost[i]].best + score[i];
					if (dp[i][v].best < tt) {
						dp[i][v].best = tt;
						dp[i][v].idsum = dp[i - 1][v - cost[i]].idsum + i;
						dp[i][v].from = v - cost[i];
						dp[i][v].selected = 1;
					}
					if (dp[i][v].best == tt) {
						int idsum1 = dp[i - 1][v - cost[i]].idsum + i;
						int idsum2 = dp[i - 1][v].idsum;
						if (idsum1 < idsum2) {
							dp[i][v].best = tt;
							dp[i][v].idsum = dp[i - 1][v - cost[i]].idsum + i;
							dp[i][v].from = v - cost[i];
							dp[i][v].selected = 1;
						}
					}
				}
			}
		}
		int costs = 0, scores = dp[N][B].best;
		vector<int> ans;
		int i = N, v = B;
		while (i >= 0) {
			if (dp[i][v].selected == 1) {
				ans.push_back(i);
				costs += cost[i];
			}
			v = dp[i][v].from;
			i--;
		}
		printf("Case #%d:\n%d %d\n", cases, scores, costs);
		if (scores == 0) continue;
		for (int i = ans.size() - 1; i >= 0; i--) {
			if (i) printf("%d ", ans[i]);
			else printf("%d\n", ans[i]);
		}
	}
	// system("pause");
	return 0;
}