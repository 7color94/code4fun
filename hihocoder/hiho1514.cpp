#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <climits>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int N, M, L;
int ans = 1e9;
vector<int> A, B, C;

void find(vector<int>& AA, vector<int>& BB, vector<int>& CC, int nn, int mm, int ll) {
    for (size_t i = 0; i < nn; i++) {
        int j = lower_bound(BB.begin(), BB.end(), AA[i]) - BB.begin();
        if (j < mm) {
            int l = lower_bound(CC.begin(), CC.end(), BB[j]) - CC.begin();
            if (l < ll) {
                ans = min(ans, 2*(CC[l] - AA[i]));
            }
        }
    }
}

void solve() {
	std::sort(A.begin(), A.end());
	std::sort(B.begin(), B.end());
	std::sort(C.begin(), C.end());

	find(A, B, C, N, M, L);
    find(A, C, B, N, L, M);
    find(C, A, B, L, N, M);
    find(B, A, C, M, N, L);
    find(C, B, A, L, M, N);
    find(B, C, A, M, L, N);
}

int main() {
	ifstream cin("in.txt");
	cin >> N >> M >> L;

	int height;
	for (int i = 0; i < N; i++) {
		cin >> height;
		A.push_back(height);
	}
	for (int i = 0; i < M; i++) {
		cin >> height;
		B.push_back(height);
	}
	for (int i = 0; i < L; i++) {
		cin >> height;
		C.push_back(height);
	}

    solve();
	cout << ans << endl;

	return 0;
}
