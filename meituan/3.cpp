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
using namespace std;

// Problem: https://www.nowcoder.com/cts/5391184/summary#4/{"uid"%3A"1AE5FF337961ED34"%2C"type"%3A"4"%2C"index"%3A1}

int main() {

    ifstream cin("in.txt");

    int m;
    while (cin >> m) {
        char op;
        int x;

        map<int, int> operations;
        vector<int> q_pos;
        
        int ans = -1;
        int has_error = false;

        for (int i = 1; i <= m; i++) {
            cin >> op;
            if (op == '?') {
                q_pos.push_back(i);
                continue;
            }
            cin >> x;

            if (has_error) continue;
            
            if (op == 'I') {
                if (operations[x] > 0) {
                    int pos = operations[x];
                    int has_find = false;
                    
                    /*
                    for (size_t p = 0; p < q_pos.size(); p++) {
                        if (q_pos[p] >= pos && q_pos[p] != -1) {
                            q_pos[p] = -1;
                            has_find = true;
                            break;
                        }
                    }
                    */
                    // use binary search, otherwise it will TLE.
                    auto low = std::lower_bound (q_pos.begin(), q_pos.end(), pos);
                    for (auto it = low; it != q_pos.end(); it++) {
                        if (*it != -1) {
                            q_pos[it - q_pos.begin()] = -1;
                            has_find = true;
                            break;
                        }
                    }

                    if (has_find == false) {
                        has_error = true;
                        ans = i;
                        continue;
                    }
                }
                operations[x] = i;
            }

            if (op == 'O') {
                if (operations[x] <= 0) {
                    int pos = -operations[x];
                    int has_find = false;
                    /*
                    for (size_t p = 0; p < q_pos.size(); p++) {
                        if (q_pos[p] >= pos && q_pos[p] != -1) {
                            q_pos[p] = -1;
                            has_find = true;
                            break;
                        }
                    }
                    */

                    auto low = std::lower_bound (q_pos.begin(), q_pos.end(), pos);
                    for (auto it = low; it != q_pos.end(); it++) {
                        if (*it != -1) {
                            q_pos[it - q_pos.begin()] = -1;
                            has_find = true;
                            break;
                        }
                    }
                    if (has_find == false) {
                        has_error = true;
                        ans = i;
                        continue;
                    }
                }
                operations[x] = -i;
            }
        }
        
        cout << ans << endl;
    }

    return 0;
}
