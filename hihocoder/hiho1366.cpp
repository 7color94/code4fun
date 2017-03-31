#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include <stack>

using namespace std;

int main() {
	int N;
	std::cin >> N;
	vector<string> strs;
	string input;
	while (N--) {
		std::cin >> input;
		strs.push_back(input);
	}
	map<string, string> mapstring;
	int count = 0;
	for (size_t i = 0; i < strs.size(); i++) {
		if (mapstring.end() == mapstring.find(strs[i])) {
			string rstrs(strs[i]);
			reverse(rstrs.begin(), rstrs.end());
			mapstring.insert(pair<string, string>(strs[i], rstrs));
			mapstring.insert(pair<string, string>(rstrs, strs[i]));
		}
		else {
			count++;
		}
	}
	std::cout << count << std::endl;
	//system("pause");
	return 0;
}