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

int n, m, x, y;
int grid[105][105];
int times[105][105];
int dirs[4][2] = {{0,-1}, {0,1}, {-1,0}, {1,0}};

int bfs_search() {
    int n1 = 1, n2 = 0, n3 = 0;
    queue< pair<int, int> > q;
    int time = 1, num = grid[x][y];
    memset(times, 0, sizeof(times));
    times[x][y] = 1;
    q.push(make_pair(x, y));
    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        int xx = p.first, yy = p.second, t = times[xx][yy] + 1;
        for (int d = 0; d < 4; d++) {
            int xxx = xx + dirs[d][0], yyy = yy + dirs[d][1];
            if (xxx < 0 || xxx >= n || yyy < 0 || yyy >= m) continue;
            if (grid[xxx][yyy] == num) {
                if (times[xxx][yyy] == t) n3++;
                if (times[xxx][yyy] == 0) {
                    n1++;
                    n2++;
                    q.push(make_pair(xxx, yyy));
                    times[xxx][yyy] = t;
                }
            }
        }   
    }
    // cout << n1 << " " << n2 << " " << n3 << endl;
    return (n1*4-n2*2-n3*2);
}

int main() {
    ifstream cin("in.txt");
    // freopen("in.txt", "r", stdin);
    cin >> n >> m >> x >> y;
    memset(grid, 0, sizeof(grid));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    int ans = bfs_search();
    cout << ans << endl;
    return 0;
}