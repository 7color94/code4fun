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

int isprime[1000010];
int primes[1000010];

int Eular(int n) {
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = isprime[1] = 0;
    memset(primes, 0, sizeof(primes));
    int primecount = 0;
    for (int i = 2; i <= n; i++) {
        if (isprime[i]) primes[++primecount] = i;
        for (int j = 1; j <= primecount; j++) {
            if (i * primes[j] > n) break;
            isprime[i * primes[j]] = 0;
            if (i % primes[j] == 0) break;
        }
    }
    return primecount;
}

int main() {
    ifstream cin("in.txt");
    // freopen("in.txt", "r", stdin);

    int n;
    cin >> n;
    cout << Eular(n) << endl;

    return 0;
}