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

unordered_map<string, int> mp;

int divide(string str) {
    if (str.size() <= 4) return str.size();
    if (mp.count(str)) return mp[str];
    int len = str.size(), ans = INT_MAX;
    // 寻找重复子串
    for (int stride = 1, j; stride <= len / 2; stride++) {
        string temp1 = str.substr(0, stride);
        for (j = 0; j <= len-stride; j+=stride) {
            string temp2 = str.substr(j, stride);
            if (temp1 != temp2) break;
        }
        if (j >= len) return 2 + to_string(len/stride).size() + divide(temp1);
    }
    // 枚举割点
    for (int stride = 1; stride < len; stride++) {
        string left = str.substr(0, stride);
        string right = str.substr(stride);
        int val1 = divide(left), val2 = divide(right);
        if (left.size() > 4) mp[left] = val1;
        if (right.size() > 4) mp[right] = val2;
        ans = min(ans, val1 + val2);
    }
    return ans;
}

int main() {
    ifstream cin("in.txt");
    // freopen("in.txt", "r", stdin);
    int t;
    cin >> t;
    while (t--) {
        string str;
        cin >> str;
        cout << divide(str) << endl;
    }
    return 0;
}