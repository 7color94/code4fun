#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <climits>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

/*
Huawei FX笔试题
Input：
5个线程（线程id，线程优先级，线程开始时间，线程执行时间）
Output：
每个时间段哪个线程（id）运行了多长时间
Solution：
直接模拟，头都炸了，有很多细节和边界处理。
本AC代码则采用多路归并算法进行模拟，方便很多。
*/

struct Cthread {
	int id;
	int priority;
	int start;
	int period;
};

vector<Cthread*> cthreads;

bool CompareById(Cthread* a, Cthread* b) {
	return a->id < b->id;
}

void solve() {
	// 5 * 201
	std::sort(cthreads.begin(), cthreads.end(), CompareById);
	vector< vector<int> > A(5, vector<int>(201, -1));
	int idx[5];
	for (size_t i = 0; i < 5; i++) {
		for (size_t j = cthreads[i]->start; j < cthreads[i]->start + cthreads[i]->period; j++) {
			A[i][j] = cthreads[i]->priority;
		}
		idx[i] = 0;
	}
	int startTime = 0, currentTime = 0;
	int oid = -1;
	while (idx[0] < 201 || idx[1] < 201 || idx[2] < 200 || idx[3] < 200 || idx[4] < 200) {
		int nid = -1, priority = -1;
		for (size_t i = 0; i < 5; i++) {
			if (idx[i] >= 201) continue;
			if (A[i][idx[i]] == -1) {
				idx[i]++;
				continue;
			}
			if (A[i][idx[i]] > priority) {
				nid = i;
				priority = cthreads[i]->priority;
			}
		}
		if (nid == -1 && oid == -1) {
			// 没有线程到达
			currentTime++;
			continue;
		} else if (nid == -1 && oid != -1) {
			// oid运行结束，此时也没有线程到达
            if (currentTime - startTime > 0) cout << (oid + 1) << "." << (currentTime - startTime) << endl;
			oid = -1;
			nid = -1;
			startTime = currentTime;
			currentTime++;
			continue;
		} 
		if (nid == oid) {
			// oid 继续运行
			idx[nid]++;
			currentTime++;
			continue;
		} else {
			// 抢占: nid != oid
			idx[nid]++;
            if (currentTime - startTime > 0) cout << (oid + 1) << "." << (currentTime - startTime) << endl;
            startTime = currentTime;
            oid = nid;
			currentTime++;
		}
	}
	// 时间片未结束
	if (startTime < 200) {
		cout << 0 << '.' << 200 - startTime << endl;
	}
}

int main() {
	ifstream cin("in.txt");
	int id, pr, start, pe;
	for (int i = 0; i < 5; i++) {
		cin >> id >> pr >> start >> pe;
		Cthread* c = new Cthread;
		c->id = id;
		c->priority = pr;
		c->start = start;
		c->period = pe;
		cthreads.push_back(c);
	}
	solve();

	return 0;
}