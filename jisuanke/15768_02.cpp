#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
#include <climits>
#include <random>
using namespace std;

// Problem: https://nanti.jisuanke.com/t/15768

#define MAXN 50050
#define MAXK 550
#define MOD 1000000007

int M, N, K;
uint64_t A[MAXN], B[MAXK], hashsum[MAXN];

// 记录每个元素的权重
map<int, int> ids;

int main() {

    ifstream cin("in.txt");
    cin >> N;

    std::random_device r;
    std::mt19937_64 e1(r());
    std::uniform_int_distribution<uint64_t> uniform_dist(0, INT_MAX);
    // int mean = uniform_dist(e1);

    for (size_t i = 0; i < N; i++) {
        cin >> A[i];

        if (ids.find(A[i]) == ids.end()) {
            // 分配一个随机无符号64位无符号整数作为A[i]元素的权重
            ids[A[i]] = uniform_dist(e1) % MOD;
        }

        if (i == 0) hashsum[i] = (ids[A[i]] * (A[i] % MOD)) % MOD;
        else hashsum[i] = (hashsum[i - 1] + ((A[i] % MOD) * ids[A[i]]) % MOD) % MOD;
    }

    cin >> M;
    for (size_t i = 0; i < M; i++) {
        cin >> K;

        // 保存B串的hash值
        int BSUM = 0;
        for (size_t j = 0; j < K; j++) {
            cin >> B[j];
            if (ids.find(B[j]) == ids.end()) {
                ids[B[j]] = uniform_dist(e1) % MOD;;
            }
            BSUM = (BSUM + ((B[j] % MOD) * ids[B[j]])) % MOD;
        }

        int ans = 0;
        int check_sum = 0;

        for (size_t ii = 0; ii + K - 1 < N; ii++) {

            if (ii == 0) {
                check_sum = hashsum[ii + K - 1];
            } else {
                check_sum = (hashsum[ii + K - 1] - hashsum[ii - 1] + MOD) % MOD;
            }
            if (check_sum == BSUM) ans++;
        }

        cout << ans << endl;
    }

    return 0;
}
