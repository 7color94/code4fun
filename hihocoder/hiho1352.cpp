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
#include <sstream>
#include <stack>
using namespace std;

int grid[1005][1005];
int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

void update(int x, int y, int id) {
    if (grid[x][y] == 0) return;
    if (grid[x][y] == id) return;
    grid[x][y] = id;
    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        if (nx >= 0 && nx < 1000 && ny >= 0 && ny < 1000) update(nx, ny, id);
    }
    return;
}

int main() {
    freopen("in.txt", "r", stdin);
    int N;
    scanf("%d", &N);
    int x, y, cnt, maxid;
    cnt = maxid = 0;
    while (N--) {
        scanf("%d %d", &x, &y);
        if (grid[x][y] != 0) continue;
        int id = maxid + 1;
        set<int> neighbors;
        for (int i = 0; i < 4; i++) {
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];
            if (nx >= 0 && nx < 1000 && ny >= 0 && ny < 1000 && grid[nx][ny] != 0) {
                id = min(id, grid[nx][ny]);
                neighbors.insert(grid[nx][ny]);
            }
        }
        grid[x][y] = id;
        for (int i = 0; i < 4; i++) {
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];
            if (nx >= 0 && nx < 1000 && ny >= 0 && ny < 1000) update(nx, ny, id);
        }
        maxid = max(id, maxid);
        cnt = cnt - neighbors.size() + 1;
        printf("%d\n", cnt);
    }
}