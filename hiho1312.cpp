#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// 362880
const int maxn = 363000;

struct state {
    int grid[3][3];
    int H;
    int F;
    int step;
    int curx;
    int cury;
    int id;
    friend bool operator<(state a, state b) {
        return a.F > b.F;
    }
};

struct state start;

bool openlist[maxn], closelist[maxn], flag = false;
int stateF[maxn];

int fac[9];
//int fac[9] = {1,1,2,6,24,120,720,5040,40320};
int moves[4][2] = {{0,1}, {1,0}, {-1,0}, {0,-1}};

int cantor(state a) {
    int val = 0, i, j;
    int number[9];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            number[3*i+j] = a.grid[i][j];
        }
    }
    for (i = 0; i < 9; i++) {
        int cnt = 0;
        for (j = i+1; j < 9; j++) {
            if (number[j] < number[i]) {
                cnt++;
            }
        }
        val += cnt * fac[8 - i];
    }
    return val;
}

int evaluate(state a) {
    int e = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int wantx = (a.grid[i][j] - 1) / 3;
            int wanty = (a.grid[i][j] - 1) % 3;
            e += abs(j - wantx) + abs(i - wanty);
        }
    }
    return e;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i < 9; i++) {
        fac[i] = fac[i - 1] * i;
    }
    for (int i = 0; i < maxn; i++) {
        openlist[i] = false;
        closelist[i] = false;
        stateF[i] = -1;
    }
    flag = false;
}

void bfs() {
    flag = false;
    priority_queue<state> openlistQ;
    int id = cantor(start);
    start.id = id;
    openlistQ.push(start);
    openlist[start.id] = true;
    stateF[start.id] = start.F;
    while (!openlistQ.empty()) {
        state cur = openlistQ.top();
        openlistQ.pop();
        stateF[cur.id] = -1;
        openlist[cur.id] = false;
        if (cur.id == 46233) {
            std::cout << cur.step << std::endl;
            flag = true;
            return;
        }
        if (closelist[cur.id]) {
            continue;
        } else {
            closelist[cur.id] = true;
        }
        for (int i = 0; i < 4; i++) {
            state next = cur;
            next.step++;
            next.curx += moves[i][0];
            next.cury += moves[i][1];
            if (next.curx < 0 || next.cury < 0 || next.curx > 2 || next.cury > 2) {
                continue;
            } else {
                int t = next.grid[next.curx][next.cury];
                next.grid[next.curx][next.cury] = next.grid[cur.curx][cur.cury];
                next.grid[cur.curx][cur.cury] = t;
                int nextId = cantor(next);
                next.id = nextId;
                next.H = evaluate(next);
                next.F = next.step + next.H;
                if (openlist[next.id]) {
                    if (next.F < stateF[next.id]) {
                        openlistQ.push(next);
                        stateF[next.id] = next.F;
                    }
                } else if (closelist[next.id]) {
                    continue;
                } else {
                    openlistQ.push(next);
                    openlist[next.id] = true;
                    stateF[next.id] = next.F;
                }
            }
        }
    }
}

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        init();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                std::cin >> start.grid[i][j];
                if (start.grid[i][j] == 0) {
                    start.curx = i;
                    start.cury = j;
                }
            }
        }
        start.step = 0;
        start.H = evaluate(start);
        start.F = start.H + start.step;
        //std::cout << cantor(start) << std::endl;
        bfs();
        if (!flag) {
            std::cout << "No Solution!" << std::endl;
        }
    }
    return 0;
}
