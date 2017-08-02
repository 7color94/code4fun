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
#include <unordered_map>
using namespace std;

char str[10000000];
int p[10000000];

int main() {
    ifstream cin("in.txt");
    // freopen("in.txt", "r", stdin);
    int T;
    string input;
    cin >> T;
    while (T--) {
        cin >> input;
        // Manacher Algorithm

        str[0] = '$';
        int idx = 1;
        int lens = input.size();
        for (int i = 0; i < lens; i++) {
            str[idx++] = '#';
            str[idx++] = input[i];
        }
        str[idx++] = '#';

        lens = idx;
        memset(p, 0, sizeof(p));
        int mx = 0, id = 0;
        int ans = -1;
        for (int i = 1; i < lens; i++) {
            p[i] = mx > i ? min(p[2*id-i], mx-i) : 0;
            while (str[i-p[i]] == str[i+p[i]]) p[i]++;
            if (mx < i + p[i]) {
                mx = i + p[i];
                id = i;
            }
            if (ans < p[i]) ans = p[i];
        }
        cout << ans - 1 << endl;
    }
    return 0;
}