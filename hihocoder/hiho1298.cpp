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
using namespace std;

int isprime[5000010];
int primes[5000010];
int phi[5000010];

int Eular(int L, int R) {
    memset(isprime, 1, sizeof(isprime));
    memset(primes, 0, sizeof(primes));
    memset(phi, 0, sizeof(phi));
    int primecc = 0;
    for (int i = 2; i <= R; i++) {
        if (isprime[i]) {
            primes[++primecc] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= primecc; j++) {
            if (i * primes[j] > R) break;
            isprime[i * primes[j]] = 0;
            if (i % primes[j] == 0) {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            } else {
                phi[i * primes[j]] = phi[i] * (primes[j] - 1);
            }
        }
    }
    int min_ans = INT_MAX, min_index = L;
    for (int i = L; i <= R; i++) {
        if (phi[i] < min_ans) {
            min_ans = phi[i];
            min_index = i;
        }
    }
    return min_index;
}

int main() {
    ifstream cin("in.txt");
    // freopen("in.txt", "r", stdin);

    int L, R;
    cin >> L >> R;
    int ans = Eular(L, R);
    cout << ans << endl;

    return 0;
}