#include<iostream>
#include<string>
#include<vector>

using namespace std;

vector<int> buildNext(string pattern) {
	size_t m = pattern.length();
	vector<int> next(m, 0);
	int k = 0;
	for (size_t i = 1; i < m; i++) {
		while (k > 0 && pattern[k] != pattern[i]) {
			k = next[k - 1];
		}
		if (pattern[k] == pattern[i]) {
			k++;
		}
		next[i] = k;
	}
	return next;
}

int KMP(string text, string pattern) {
	vector<int> matchPoints;
	vector<int> next = buildNext(pattern);
	size_t m = pattern.length(), n = text.length();
	int k = 0;
	for (size_t i = 0; i < n; i++) {
		while (k > 0 && pattern[k] != text[i]) {
			k = next[k - 1];
		}
		if (pattern[k] == text[i]) {
			k++;
		}
		if (k == m) {
			matchPoints.push_back(i);
			k = next[k - 1];
		}
	}
	return matchPoints.size();
}

int main() {
	int n;
	cin >> n;
	string text, pattern;
	while (n--) {
		cin >> pattern;
		cin >> text;
		cout << KMP(text, pattern) << endl;
	}
	return 0;
}