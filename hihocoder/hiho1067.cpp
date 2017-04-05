#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int N, M;

struct node {
	string name;
	int color = 0; // white 0, gray 1, black -1
	struct node* parent = NULL;
	vector<struct node*> childs;
	vector<int> queryids;
};

map<string, int> name2id;
vector<struct node*> allnodes;
vector<pair<string, string>> querys;

void add_f_c(string father, string child, vector<int>& setid) {
	if (name2id[father] == 0) {
		struct node* f_node = new node();
		f_node->name = father;
		f_node->color = 0;
		allnodes.push_back(f_node);
		name2id[father] = allnodes.size();
	}
	if (name2id[child] == 0) {
		struct node* c_node = new node();
		c_node->name = child;
		c_node->color = 0;
		allnodes.push_back(c_node);
		name2id[child] = allnodes.size();
	}
	allnodes[name2id[father] - 1]->childs.push_back(allnodes[name2id[child] - 1]);
	setid[name2id[father] - 1] = name2id[father] - 1;
	allnodes[name2id[child] - 1]->parent = allnodes[name2id[father] - 1];
	setid[name2id[child] - 1] = name2id[child] - 1;
}

void add_query(string q1, string q2, int qid) {
	allnodes[name2id[q1] - 1]->queryids.push_back(qid);
	allnodes[name2id[q2] - 1]->queryids.push_back(qid);
	querys.push_back(make_pair(q1, q2));
}

void dfs(struct node* cur, vector<string>& ans, vector<int>& setid) {
	// change to gray
	cur->color = 1;
	for (int i = 0; i < cur->queryids.size(); i++) {
		int qid = cur->queryids[i];
		if (ans[qid] != "") {
			continue;
		}
		pair<string, string> cur_q = querys[qid];
		if (cur_q.first == cur->name) {
			if (allnodes[name2id[cur_q.second] - 1]->color == 1) {
				ans[qid] = cur_q.second;
			}
			if (allnodes[name2id[cur_q.second] - 1]->color == -1) {
				int id = setid[name2id[cur_q.second] - 1];
				while (allnodes[id]->color != 1) {
					id = setid[id];
					
				}
				int ii = setid[name2id[cur_q.second] - 1];
				int j;
				while (ii != id) {
					j = setid[ii];
					setid[ii] = id;
					ii = j;
				}
				ans[qid] = allnodes[id]->name;
			}
		}
		if (cur_q.second == cur->name) {
			if (allnodes[name2id[cur_q.first] - 1]->color == 1) {
				ans[qid] = cur_q.first;
			}
			if (allnodes[name2id[cur_q.first] - 1]->color == -1) {
				int id = setid[name2id[cur_q.first] - 1];
				while (allnodes[id]->color != 1) {
					id = setid[id];
				}
				ans[qid] = allnodes[id]->name;
			}
		}
	}
	for (int i = 0; i < cur->childs.size(); i++) {
		dfs(cur->childs[i], ans, setid);
	}
	// change to black
	cur->color = -1;
	// change set
	if (cur->parent != NULL) {
		setid[name2id[cur->name] - 1] = name2id[cur->parent->name] - 1;
	}
}

int main() {
	ifstream cin("input.txt");
	cin >> N;
	string father_i, child_i;
	vector<int> setid(N + 1, 0);
	while (N--) {
		cin >> father_i;
		cin >> child_i;
		add_f_c(father_i, child_i, setid);
	}
	cin >> M;
	string q1, q2;
	vector<string> ans(M, "");
	for (int i = 0; i < M; i++) {
		cin >> q1;
		cin >> q2;
		add_query(q1, q2, i);
		if (q1 == q2) {
			ans[i] = q1;
		}
	}
	dfs(allnodes[0], ans, setid);
	for (auto a : ans) {
		cout << a << endl;
	}
	return 0;
}