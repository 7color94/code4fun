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

int N, k;
int num[1000100];

void swap(int ii, int jj) {
    int tt = num[ii];
    num[ii] = num[jj];
    num[jj] = tt;
}

int partition(int start, int end) {
    int key = num[end];
    int i = start - 1;
    for (int j = start; j < end; j++) {
        if (num[j] < key) swap(++i, j);
    }
    swap(++i, end);
    return i;
}

int binary_search_k(int start, int end, int kk) {
    if (start <= end) {
        int pos = partition(start, end);
        int cc = pos - start + 1;
        if (kk < cc) return binary_search_k(start, pos - 1, kk);
        else if (kk > cc) return binary_search_k(pos + 1, end, kk - cc);
        else return num[pos];
    } else {
        return -1;
    }
}

int main() {
    ifstream cin("in.txt");
    
    cin >> N >> k;
    for (int i = 0; i < N; i++) {
        cin >> num[i];
    }

    int ans = binary_search_k(0, N - 1, k);
    cout << ans << endl;

    return 0;
}