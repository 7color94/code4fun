#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include <stack>

using namespace std;

int main() {
	int lens, cc = 0;
	std::cin >> lens;
	stack<int> s;
	for (int i = 0; i < lens; i++) {
		int num;
		std::cin >> num;
		if (!s.empty() && (s.top() + num) % 2 == 1) {
			s.pop();
			cc += 2;
		}
		else {
			s.push(num);
		}
	}
	std::cout << lens - cc << std::endl;
}