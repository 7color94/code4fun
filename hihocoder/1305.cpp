#include<iostream>
#include<fstream>
#include<math.h>
#include<algorithm>
#include<vector>
using namespace std;

int N, M;

struct node {
    int p;
    // A_left 0, A_right 1, B_left 2, B_right 3
    int color;
    node(int p, int color): p(p), color(color) {}
};

vector<node> nodes;

bool cmpp(const node &a, const node &b) {
    return a.p < b.p;
}

int solve() {

    std::sort(nodes.begin(), nodes.end(), cmpp);
    /*
    for (int i = 0; i < 2*(N + M); i++) {
        cout << nodes[i].p << " " << nodes[i].color << endl;
    }
    */
    int cntA = 0, cntB = 0;
    int left = 0, right = 0;
    int ans = 0;
    for (int i = 0; i < 2*(N + M); i++) {
        if (nodes[i].color == 0) cntA++;
        if (nodes[i].color == 1) cntA--;
        if (nodes[i].color == 2) cntB++;
        if (nodes[i].color == 3) cntB--;

        // cout << "cntA: " << cntA << ", cntB: " << cntB << endl;

        if (cntA > 0 && cntB == 0) {
            if (left == 0) left = nodes[i].p;
            // cout << "left: " << left << endl;
        }
        if (cntA > 0 && cntB > 0) {
            if (left != 0) {
                right = nodes[i].p;
                // cout << "right: " << right << endl;
                ans = ans + (right - left);
                left = 0;
                right = 0;
            }
        }
        if (cntA == 0 && cntB == 0) {
            if (left != 0) {
                right = nodes[i].p;
                // cout << "right: " << right << endl;
                ans = ans + (right - left);
                left = 0;
                right = 0;
            }
        }
    }
    return ans;
}

int main() {

    ifstream cin("in.txt");
    cin >> N >> M;

    int left, right;
    nodes.clear();

    for (int i = 0; i < N; i++) {
        cin >> left >> right;
        node nn = node(left, 0);
        node mm = node(right, 1);
        nodes.push_back(nn);
        nodes.push_back(mm);
    }

    for (int i = 0; i < M; i++) {
        cin >> left >> right;
        node nn = node(left, 2);
        node mm = node(right, 3);
        nodes.push_back(nn);
        nodes.push_back(mm);
    }

    int ans = solve();
    cout << ans << endl;

    return 0;
}
