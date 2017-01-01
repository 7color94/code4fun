#include<iostream>

using namespace std;

struct day {
    int idx;
    int l;
    int r;
    int intervals;
};

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        std::cin >> N >> M;
        day days[N];
        int idx;
        for (int i = 0; i < N; i++) {
            std::cin >> idx;
            days[i].idx = idx;
        }
        int max = -1;
        if (M >= N) {
            std::cout << 100 << std::endl;
            continue;
        }
        for (int i = 0; i <= N - M; i++) {
            // i, i+1, ..., i+M
            int left = 0;
            if (i-1 >= 0 ){
                left = days[i-1].idx;
            }
            int right = 101;
            if (i+M < N) {
                right = days[i+M].idx;
            }
            if (right - left - 1 > max) {
                max = right - left - 1;
            }
        }
        std::cout << max << std::endl;
    }
}
