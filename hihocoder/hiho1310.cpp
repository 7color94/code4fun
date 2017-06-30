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
#include <utility>
using namespace std;

int N, M;
char mmap[55][55];
int vis[55][55];
int color[55][55];
int shape_vis[3000];
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct node {
    int delta_x, delta_y;
    node(int xx, int yy): delta_x(xx), delta_y(yy){}
};

vector< node > shape;

void dfs(int ii, int jj, int cc, int &area, int starti, int startj) {
    if (vis[ii][jj] == 1 || mmap[ii][jj] != '#') return;

    vis[ii][jj] = 1;
    color[ii][jj] = cc;
    area++;

    int delta_x = jj - startj;
    int delta_y = ii - starti;
    node _node = node(delta_x, delta_y);
    shape.push_back(_node);

    for (int d = 0; d < 4; d++) {
        int nii = ii + directions[d][0];
        int njj = jj + directions[d][1];
        if (nii < 0 || nii >= N || njj < 0 || njj >= M) continue;
        dfs(nii, njj, cc, area, starti, startj);
    }
}


int main() {
    ifstream cin("in.txt");
    cin >> N >> M;

    char c;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> mmap[i][j];
        }
    }

    memset(vis, 0, sizeof(vis));
    int num = 1;
    set<int> areas;
    vector< vector< node > > shapes;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (vis[i][j] == 0 && mmap[i][j] == '#') {
                int area = 0;
                // vector< pair<int, int> > shape;
                shape.clear();
                
                dfs(i, j, color[i][j], area, i, j);
                
                shapes.push_back(shape);
                areas.insert(area);
                num++;
            }
        }
    }

    int ans1 = areas.size();
    
    memset(shape_vis, 0, sizeof(shape_vis));
    int ans2 = 0;
    for (int i = 0; i < shapes.size(); i++) {
        if (shape_vis[i] == 1) continue;
        for (int j = i + 1; j < shapes.size(); j++) {
            if (shapes[i].size() == shapes[j].size() && shape_vis[j] == 0) {
                int flag = 1;
                for (int t = 0; t < shapes[i].size(); t++) {
                    if (shapes[i][t].delta_x != shapes[j][t].delta_x || shapes[i][t].delta_y != shapes[j][t].delta_y) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) shape_vis[j] = 1;
            }
        }
        shape_vis[i] = 1;
        ans2++;
    }
   
    cout << num - 1 << " " << ans1 << " " << ans2 << endl;

    return 0;
}