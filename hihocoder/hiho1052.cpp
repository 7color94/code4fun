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

int T, k, len;
char str[1010];

int solve1() {
    int ans = 0;
    for (int i = 0; i < k; i++) {
        if (str[i] != str[len - k + i]) ans++;
    }
    return ans;
}

int solve2() {
    int interval = len - k;
    int ans = 0;
    for (int i = 0; i < interval; i++) {
        // A T C G
        int count[4] = {0, 0, 0, 0};
        int cc = 0;
        for (int j = i; j < len; j += interval) {
            if (str[j] == 'A') count[0]++;
            if (str[j] == 'T') count[1]++;
            if (str[j] == 'C') count[2]++;
            if (str[j] == 'G') count[3]++;
            cc++;
        }
        int _m = max(max(count[2], max(count[0], count[1])), count[3]);
        ans += (cc - _m);
    }
    return ans;
}

int main() {
    //ifstream cin("in.txt");
    freopen("in.txt", "r", stdin);
    
    cin >> T;
    while (T--) {
        scanf("%s", str);
        cin >> k;
        
        int ans = 0;
        len = strlen(str);
        if (2 * k <= len) ans = solve1();
        else ans = solve2();

        cout << ans << endl;
    }

    return 0;
}