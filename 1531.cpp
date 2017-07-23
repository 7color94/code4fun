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

int n, k;

struct person {
    int totalnum;
    int type; // 0 is fruit, 1 is animal
    int fruits[4];
    int animal[3];
    int num; // nums on table
    person(): totalnum(10000000), type(-1), num(0) {
        for (int i = 0; i < 4; i++) fruits[i] = 0;
        for (int i = 0; i < 3; i++) animal[i] = 0;
    }
} ps[11];

bool is_ring() {
    int fruits_num[4] = {0, 0, 0, 0};
    int exist_monkey = 0, exist_elephant = 0, exist_pig = 0;
    int exist_fruit = 0, exist_linmeng = 0, exist_caomei = 0;
    for (int p = 0; p < n; p++) {
        if (ps[p].type == 0) {
            fruits_num[0] += ps[p].fruits[0];
            fruits_num[1] += ps[p].fruits[1];
            fruits_num[2] += ps[p].fruits[2];
            fruits_num[3] += ps[p].fruits[3];
            if (ps[p].fruits[1]) exist_caomei = 1;
            if (ps[p].fruits[3]) exist_linmeng = 1;
            if (ps[p].fruits[0] || ps[p].fruits[1] || ps[p].fruits[2] || ps[p].fruits[3]) exist_fruit = 1;
        } else {
            if (ps[p].animal[0]) exist_monkey = 1;
            if (ps[p].animal[1]) exist_elephant = 1;
            if (ps[p].animal[2]) exist_pig = 1;
        }
    }
    if (fruits_num[0] == 5 || fruits_num[1] == 5 || fruits_num[2] == 5 || fruits_num[3] == 5) return true;
    if (exist_monkey && exist_fruit && !exist_linmeng) return true;
    if (exist_elephant && exist_fruit && !exist_caomei) return true;
    if (exist_pig && exist_fruit) return true;
    return false;
}

void reset_p(int pid) {
    ps[pid].num = 0;
    ps[pid].type = -1;
    for (int i = 0; i < 4; i++) ps[pid].fruits[i] = 0;
    for (int i = 0; i < 3; i++) ps[pid].animal[i] = 0;
}

int main() {
    ifstream cin("in.txt");
    // freopen("in.txt", "r", stdin);
    
    cin >> n >> k;
    int cur_pid = 0;
    string type;
    for (int line = 1; line <= k; line++) {
        // cout << cur_pid << endl;
        cin >> type;
        if (type == "Fruit") {
            ps[cur_pid].totalnum--;
            ps[cur_pid].num++;
            ps[cur_pid].type = 0;
            ps[cur_pid].fruits[0] = ps[cur_pid].fruits[1] = ps[cur_pid].fruits[2] = ps[cur_pid].fruits[3] = 0;
            int s, fruit_id;
            cin >> s;
            for (int i = 1; i <= s; i++) {
                cin >> fruit_id;
                ps[cur_pid].fruits[fruit_id]++;
            }
            cur_pid = (cur_pid + 1) % n;
        } else if (type == "Animal") {
            ps[cur_pid].totalnum--;
            ps[cur_pid].num++;
            ps[cur_pid].type = 1;
            ps[cur_pid].animal[0] = ps[cur_pid].animal[1] = ps[cur_pid].animal[2] = 0;
            int animal_id;
            cin >> animal_id;
            ps[cur_pid].animal[animal_id]++;
            cur_pid = (cur_pid + 1) % n;
        } else {
            // type == "Ring"
            int ring_id;
            cin >> ring_id;
            bool ok = is_ring();
            if (ok) {
                int fetch_num = 0;
                for (int p = 0; p < n; p++) {
                    fetch_num += ps[p].num;
                    reset_p(p);
                }
                ps[ring_id].totalnum += fetch_num;
            } else {
                for (int p = 0; p < n; p++) {
                    if (p == ring_id) continue;
                    ps[p].totalnum++;
                    ps[ring_id].totalnum--;
                }
            }
            cur_pid = ring_id;
        }
        // for (int p = 0; p < n; p++) {
        //     cout << ps[p].totalnum << " " << ps[p].num << endl;
        // }
        // cout << endl;
    }
    
    for (int p = 0; p < n; p++) {
        cout << ps[p].totalnum << endl;
    }

    return 0;
}