#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<set>

using namespace std;

class Solution {
public:
	void unions(vector<int>& sz, vector<int>& id, int p, int q) {
		int pid = find(id, p);
		int qid = find(id, q);
		if (pid == qid) {
			return;
		}
		if (sz[pid] < sz[qid]) {
			id[pid] = qid;
			sz[qid] += sz[pid] ;
		} else {
			id[qid] = pid;
			sz[pid] += sz[qid];
		}
	}

	int find(vector<int>& id, int p) {
		/*
		while (p != id[p]) {
			id[p] = find(id, id[p]);
			p = id[p];
		}*/
		int father;
		if (p != id[p]) {
			father = find(id, id[p]);
			id[p] = father;
			return father;
		}
		return p;
	}

	int numIslands(vector<vector<char>>& grid) {
		int rows = grid.size();
		if (rows == 0) {
			return 0;
		}
		int cols = grid[0].size();
		vector<int> sz(rows*cols);
		vector<int> id(rows*cols);
		for (int i = 0; i < rows*cols; i++) {
			sz[i] = 1;
			id[i] = i;
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				int idx = i * cols + j;
				if (grid[i][j] == '0') {
					id[idx] = -1;
					continue;
				}
				// 1
				if (i > 0 && grid[i-1][j] == '1') {
					unions(sz, id, idx, (i - 1)*cols + j);
				}
				if (j > 0 && grid[i][j - 1] == '1') {
					unions(sz, id, idx, i*cols + (j - 1));
				}
				if (i + 1 < rows && grid[i + 1][j] == '1') {
					unions(sz, id, idx, (i + 1)*cols + j);
				}
				if (j + 1 < cols && grid[i][j + 1] == '1') {
					unions(sz, id, idx, i*cols + (j + 1));
				}
			}
		}
		int count = 0;
		//std::sort(id.begin(), id.end());
		/*
		int val = 0;
		int k;
		for (k = 0; k < rows*cols; k++) {
			if (id[k] != -1) {
				val = id[k];
				count++;
				break;
			}
		}*/
		std::set<int> fas;
		for (int i = 0; i < rows*cols; i++) {
			if (id[i] == -1) {
				continue;
			} else {
				fas.insert(find(id, id[i]));
			}
		}

		return fas.size();
	}
};

int main() {
	Solution s;
	//["111111","100001","101101","100001","111111"]
	// ["10111","10101","11101"]
	vector<char> g1{ '1','0','1','1','1' };
	vector<char> g2{ '1','0','1','0','1' };
	vector<char> g3{ '1','1','1','0','1' };
	//vector<char> g4{ '1','1','1','1','1', '1' };
	vector<vector<char>> grid{g1, g2, g3};
 	std::cout << s.numIslands(grid) << std::endl;
	return 0;
}
