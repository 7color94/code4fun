#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstring>
#include <climits>
using namespace std;

// Problem: https://nanti.jisuanke.com/t/15768

#define MAXN 200005

int M, N, K;
int A[MAXN], B[MAXN];

int counts[200005];
// do not use map<int, int>. it will TLE...
unordered_map<int, int> ids;

int main() {

    ifstream cin("in.txt");
    cin >> N;

    int totals = 1;
    // 预先从unordered map中取出相应value，否则每次都从map中取，会超时
    int idii, idjj, idkk;

    for (size_t i = 0; i < N; i++) {
        cin >> A[i];
        if (ids.find(A[i]) == ids.end()) {
            ids[A[i]] = totals++;
        }
    }

    cin >> M;
    for (size_t i = 0; i < M; i++) {
        cin >> K;
        memset(counts, 0, sizeof(counts));
        int cnt = 200000;

        for (size_t j = 0; j < K; j++) {
            cin >> B[j];
            if (ids.find(B[j]) == ids.end()) {
                ids[B[j]] = totals++;
            }
            idjj = ids[B[j]];
            if (counts[idjj] == 0) cnt--;
            counts[idjj]--;
        }

        int ans = 0;
        for (size_t ii = 0; ii + K - 1 < N; ii++) {
            if (ii == 0) {
                for (size_t j = 0; j < K; j++) {
                    idjj = ids[A[j]];
                    if (counts[idjj] == 0) cnt--;
                    counts[idjj]++;
                    if (counts[idjj] == 0) cnt++;
                }
            } else {
                // 离开滑窗的字符
                idii = ids[A[ii - 1]];
                if (counts[idii] == 0) cnt--;
                counts[idii]--;
                if (counts[idii] == 0) cnt++;

                // 进入滑窗的字符
                idkk = ids[A[ii + K - 1]];
                if (counts[idkk] == 0) cnt--;
                counts[idkk]++;
                if (counts[idkk] == 0) cnt++;
            }
            if (cnt == 200000) ans++;
        }

        cout << ans << endl;
    }

    return 0;
}
