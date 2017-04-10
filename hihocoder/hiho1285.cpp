#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <cstring>
#include <cmath>
#include <climits>
using namespace std;

int Q, N, M, S, T;
int A[1005];
int dp[1005][1005];

int main() {
	scanf("%d", &Q);
	while (Q--) {
		scanf("%d %d %d %d", &N, &M, &S, &T);
		for (int i = 1; i <= N; i++) {
			scanf("%d", &A[i]);
		}

		fill_n(dp[0], 1005*1005, INT_MAX);
		// handle 1st one
		for (int k = 1; k <= M; k++) {
			int c;
			for (c = 0; c*S < A[1]; c++) {
				int e = (A[1] - c*S) / T;
				if ((A[1] - c*S) % T != 0) {
					e++;
				}
				if (c + e <= k) {
					dp[1][c+e] = min(dp[1][c+e], c);
				}
			}
			if (c <= k) {
				dp[1][c] = min(dp[1][c], c);
			}
		}
		// handle 2..N
		for (int i = 2; i <= N; i++) {
			for (int k = 1; k <= M; k++) {
				int c = 0;
				for (c = 0; c*S < A[i]; c++) {
					int e = (A[i] - c*S) / T;
					if ((A[i] - c*S) % T != 0) {
						e++;
					}
					if (c+e < k && dp[i-1][k-c-e] != INT_MAX) {
						dp[i][k] = min(dp[i][k], dp[i-1][k-c-e]+c);
					}
				}
				if (c < k && dp[i-1][k-c] != INT_MAX) {
					dp[i][k] = min(dp[i][k], dp[i-1][k-c]+c);
				}
			}
		}
		int ans = INT_MAX;
		for (int k = 1; k <= M; k++) {
			ans = min(ans, dp[N][k]);
		}
		if (ans > M) {
			printf("No\n");
		} else {
			printf("%d\n", ans);
		}
	}

	return 0;
}