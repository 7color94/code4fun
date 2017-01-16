#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<map>

using namespace std;

string update(string data) {
	bool flag = true;
	string tmp, tmp2;
	data = " " + data + " ";
	while (flag) {
		flag = false;
		tmp = "";
		for (int i = 1; i < data.length() - 1; i++)
		{
			if (data[i] != data[i - 1] && data[i] != data[i + 1])
				tmp += data[i];
		}
		tmp2 = data.substr(1, data.length() - 2);
		if (tmp != tmp2)
		{
			flag = true;
			data = tmp;
			data = " " + data + " ";
		}
	}
	return tmp;
}

int solve(string input) {
	int n = input.size();
	vector<char> besides{'A', 'B', 'C'};
	int maxC = 0;
	for (int i = 0; i < n; i++) {
		for (size_t j = 0; j < besides.size(); j++) {
			string uinput = input.substr(0, i) + besides[j] + input.substr(i, n - i);
			string upinput = update(uinput);
			int count = uinput.size() - upinput.size();
			maxC = max(maxC, count);
		}
	}
	return maxC;
}

int main() {
	int N;
	std::cin >> N;
	string input;
	while (N--) {
		std::cin >> input;
		//std::cout << update(input) << std::endl;
		std::cout << solve(input) << std::endl;
	}
	//system("pause");
	return 0;
}