#include<iostream>
#include<map>
#include<cstring>
#include<climits>
#include<fstream>
#include<string>
#include<cmath>

using namespace std;

int N, Q;
int L, R;
int dp[1000000][20];

int main() {
    //ifstream cin("in.txt");
    cin >> N;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &dp[i][0]);
        //cin >> dp[i][0];
    }
    for (int j = 1; (1 << j) <= N; j++) {
        for (int i = 1; i + (1 << j) - 1 <= N; i++) {
            dp[i][j] = min(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
        }
    }
    cin >> Q;
    while (Q--) {
        //cin >> L;
        //cin >> R;
        scanf("%d %d", &L, &R);
        int T = log(R-L+1) / log(2);
        printf("%d\n", min(dp[L][T], dp[R-(1<<T)+1][T]));
    }
    return 0;
}