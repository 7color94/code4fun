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

int T;
char num[110];

int main() {
    // ifstream cin("in.txt");
    freopen("in.txt", "r", stdin);
    
    scanf("%d", &T);
    while (T--) {
        scanf("%s", num);
        vector<int> bins;
        int len = strlen(num);
        int iters = len - 2;
        int b = 0, c = 0, t = 0;
        while (iters--) {
            for (int i = len - 1; i >= 0; i--) {
                if (num[i] == '.') continue;
                c = (num[i] - '0') * 2;
                num[i] = (c % 10 + t) + '0';
                t = c / 10;
            }
            b = num[0] - '0';
            bins.push_back(b);
            num[0] = '0';
        }
        
        int no = false;
        for (int i = 2; i < len; i++) {
            if (num[i] != '0') {
                no = true;
                break;
            }
        }
        if (no) {
            cout << "NO" << endl;
        } else {
            cout << "0.";
            for (int i = 0; i < bins.size(); i++) {
                cout << bins[i];
            }
            cout << endl;
        }
    }

    return 0;
}