#include <iostream>
#include <bitset>
#include <fstream>
using namespace std;

int N;
int ranks[30010][5];
int rev_rank[30010][5];
bitset<30010> better[30010][5], t;

int main() {
	ifstream cin("in.txt");
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> ranks[i][j];
			rev_rank[ranks[i][j]][j] = i;
		}
	}

	for (int j = 0; j < 5; j++) {
		better[1][j] = 0;
		for (int r = 2; r <= N; r++) {
			better[r][j] = better[r - 1][j];
			// better[r][j].set(rev_rank[r - 1][j]);
			better[r][j][rev_rank[r - 1][j]] = 1;
		}
	}

	for (int i = 1; i <= N; i++) {
		t = better[ranks[i][0]][0];
		for (int j = 1; j < 5; j++) {
			t = t & better[ranks[i][j]][j];
		}
		cout << t.count() << endl;
	}

	return 0;
}