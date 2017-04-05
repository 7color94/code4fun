#include<iostream>
#include<math.h>

using namespace std;

long long N, M;

long long cal_y_n(long long n) {
    long long count = 0;
    long long _n = sqrt(n);
    if (_n * _n == n) {
        count = 1;
        _n = _n - 1;
    }
    for (long long i = 1; i <= _n; i++) {
        if (n % i == 0) {
            count += 2;
        }
    }
    return count;
}

long long cal_m_y(long long a, long long b) {
    if (a < b) {
        long long t = b;
        b = a;
        a = t;
    }
    long long c = 0;
    while (b) {
        c = a;
        a = b;
        b = c % b;
    }
    return a;
}

int main() {
    cin >> N;
    cin >> M;
    long long nn = cal_y_n(N);
    long long mm = cal_y_n(M);
    long long fenmu = nn * mm;
    long long t = cal_m_y(N, M);
    long long fenzi = cal_y_n(t);
    long long tmp = cal_m_y(fenmu, fenzi);
    cout << fenmu / tmp << " " << fenzi / tmp << endl;
    return 0;
}