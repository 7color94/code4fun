#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>
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
#include <sstream>
#include <stack>
using namespace std;

const int maxn = 2000 + 5;

int main() {
    freopen("in.txt", "r", stdin);
    int N, P, Q;
    scanf("%d %d %d", &N, &P, &Q);
    unordered_map< int, int > matrixA[maxn], matrixB[maxn];
    int i, j, k;
    for (int t = 0; t < P; t++) {
        scanf("%d %d %d", &i, &j, &k);
        matrixA[i].insert(make_pair(j, k));
    }
    for (int t = 0; t < Q; t++) {
        scanf("%d %d %d", &i, &j, &k);
        matrixB[j].insert(make_pair(i, k));
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            long long value = 0;
            for (unordered_map<int, int>::iterator iterA = matrixA[i].begin(); iterA != matrixA[i].end(); iterA++) {
                unordered_map<int, int>::iterator iterB = matrixB[j].find(iterA->first);
                if (iterB != matrixB[j].end()) {
                    value += (iterA->second * iterB->second);
                }
                // for (unordered_map<int, int>::iterator iterB = matrixB[j].begin(); iterB != matrixB[j].end(); iterB++) {
                //     if (iterA->first == iterB->first) {
                //         value += (iterA->second * iterB->second);
                //     }
                // }
            }
            if (value != 0) printf("%d %d %lld\n", i, j, value);
            // printf("%d %d %lld\n", i, j, value);
        }
    }
    return 0;
}