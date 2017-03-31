#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<string>
#include<fstream>

using namespace std;

int main() {
	//ifstream cin("in.txt");
	//ofstream cout("out.txt");
	int N;
	cin >> N;
	string cc;
	cin >> cc;
	int M;
	cin >> M;
	int ills[26][26] = { 0 };
	while (M--) {
		string no;
		cin >> no;
		ills[no[0] - 'a'][no[1] - 'a'] = 1;
		ills[no[1] - 'a'][no[0] - 'a'] = 1;
	}
	vector<vector<int>> dp(N, vector<int>(26, 0));
	dp[0][cc[0] - 'a'] = 1;
	for (int i = 1; i < N; i++) {
		// cc[i]
		for (int j = 0; j < 26; j++) {
			if (dp[i - 1][j] != 0) {
				dp[i][j] = dp[i - 1][j];
			}
		}
		for (int j = 0; j < 26; j++) {
			if (dp[i - 1][j] != 0) {
				if (ills[cc[i] - 'a'][j] == 1) {
					dp[i][cc[i] - 'a'] = max(1, dp[i][cc[i] - 'a']);
				}
				else {
					dp[i][cc[i] - 'a'] = max(dp[i - 1][j] + 1, dp[i][cc[i] - 'a']);
				}
			}
		}
	}
	int maxd = 0;
	for (int i = 0; i < 26; i++) {
		maxd = max(dp[N - 1][i], maxd);
	}
	cout << N - maxd << endl;
	return 0;
}