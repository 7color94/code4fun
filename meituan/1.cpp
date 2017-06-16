#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
#include <climits>
#include <random>
#include <queue>
#include <cmath>
using namespace std;


// Problem: https://www.nowcoder.com/cts/5391184/summary#4/{"uid"%3A"1AE5FF337961ED34"%2C"type"%3A"4"%2C"index"%3A1}

int main() {

    ifstream cin("in.txt");

    int n;
    cin >> n;

    int m;
    cin >> m;

    int score;
    int count = 0;
    for (int i = 1; i < n; i++) {
        cin >> score;
        if (score <= m) count++;
    }

    // cout << count << endl;
    // cout << log2(count + 1) << endl;
    int ans = floor(log2(count + 1));
    cout << ans << endl;

    return 0;
}
