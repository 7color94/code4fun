#include<iostream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;

class Solution {
public:
	int cal(char oper, int a, int b) {
		if (oper == '+') {
			return a + b;
		}
		if (oper == '-') {
			return a - b;
		}
		return a * b;
	}

	vector<int> diffWaysToCompute(string input) {
		vector<int> res;
		for (int i = 0; i < input.size(); i++) {
			if (input[i] < '0' || input[i] > '9') {
				string left = input.substr(0, i);
				string right = input.substr(i+1);
				//std::cout << left.c_str() << " " << right.c_str() << std::endl;
				vector<int> left_res = diffWaysToCompute(left);
				vector<int> right_res = diffWaysToCompute(right);
				for (int ll = 0; ll < left_res.size(); ll++) {
					for (int rr = 0; rr < right_res.size(); rr++) {
						res.push_back(cal(input[i], left_res[ll], right_res[rr]));
					}
				}
			}
		}
		if (res.empty()) {
			res.push_back(std::stoi(input));
		}
		return res;
	}
};

int main() {
	Solution s;
	s.diffWaysToCompute("2*3-4*5");
	system("pause");
}