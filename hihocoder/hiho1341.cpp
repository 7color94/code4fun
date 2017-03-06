#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <climits>
#include <string>

#define random(x) (rand()%x)

using namespace std;

int main() {
	int n;
	//ifstream cin("input.txt");
	//ofstream cout("output.txt");
	cin >> n;
	vector<string> cts;
	int v[26] = { 0 };
	while (n--) {
		string c;
		cin >> c;
		cts.push_back(c);
	}
	int k = 0;
	for (size_t i = 0; i < cts.size(); i++) {
		for (size_t j = 0; j < cts[i].size(); j++) {
			if (cts[i][j] >= 'A' && cts[i][j] <= 'Z') {
				v[cts[i][j] - 'A'] = 1;
			}
		}
	}
	for (size_t i = 0; i < 26; i++) {
		if (v[i] == 1) {
			k++;
		}
	}
	int T;
	cin >> T;
	while (T--) {
		std::map<char, int> vv;
		char c;
		int value;
		for (int i = 1; i <= k; i++) {
			cin >> c;
			cin >> value;
			vv[c] = value;
		}
		bool success = true;
		for (size_t i = 0; i < cts.size(); i++) {
			if (!success) {
				break;
			}
			string num = "";
			int value = -1;
			int flag = 0;
			for (size_t j = 0; j < cts[i].size(); j++) {
				if (cts[i][j] >= 'A' && cts[i][j] <= 'Z') {
					if (value != -1) {
						if (1 == flag) {
							if (value <= vv[cts[i][j]]) {
								value = vv[cts[i][j]];
								continue;
							} else {
								success = false;
								break;
							}
						}
						if (0 == flag) {
							if (value < vv[cts[i][j]]) {
								value = vv[cts[i][j]];
								continue;
							} else {
								success = false;
								break;
							}
						}
					} else {
						value = vv[cts[i][j]];
					}
				} else if (cts[i][j] == '<') {
					if (cts[i][j + 1] == '=') {
						flag = 1;
						j++;
					} else {
						flag = 0;
					}
				} else {
					num += cts[i][j];
					size_t t;
					for (t = j + 1; t < cts[i].size(); t++) {
						if (cts[i][t] != '<') {
							num += cts[i][t];
						} else {
							break;
						}
					}
					int _num = std::stoi(num);
					num = "";
					if (value != -1) {
						if (1 == flag) {
							if (value <= _num) {
								value = _num;
							} else {
								success = false;
								break;
							}
						}
						if (0 == flag) {
							if (value < _num) {
								value = _num;
							} else {
								success = false;
								break;
							}
						}
					} else {
						value = _num;
					}
					j = t - 1;
				}
			}
		}
		if (success) {
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
	}
	return 0;
}