#include<iostream>
#include<string>
#include<algorithm>
#include<queue>

using namespace std;

#define CHAR_RANGE 26

struct TrieNode {
	int flag;
	TrieNode *child[CHAR_RANGE];
	TrieNode *suffix;
	TrieNode(): flag(0), suffix(NULL) {
		for (int i = 0; i < CHAR_RANGE; i++) {
			child[i] = NULL;
		}
	}
};

void buildTrieTree(TrieNode *current, string &s, int idx) {
	int n = s.length();
	if (idx == n) {
		current->flag = 1;
		return;
	}
	int index = s[idx] - 'a';
	if (current->child[index] == NULL) {
		current->child[index] = new TrieNode();
	}
	buildTrieTree(current->child[index], s, idx + 1);
}

void buildAC(TrieNode *root) {
	queue<TrieNode*> qt;
	qt.push(root);
	while (!qt.empty()) {
		TrieNode *current = qt.front();
		qt.pop();
		for (int i = 0; i < CHAR_RANGE; i++) {
			if (current->child[i] != NULL) {
				if (current == root) {
					current->child[i]->suffix = root;
					qt.push(current->child[i]);
					continue;
				}
				TrieNode *currentSuffix = current->suffix;
				while (currentSuffix != NULL) {
					if (currentSuffix->child[i] != NULL) {
						current->child[i]->suffix = currentSuffix->child[i];
						break;
					}
					currentSuffix = currentSuffix->suffix;
				}
				if (currentSuffix == NULL) {
					current->child[i]->suffix = root;
				}
				qt.push(current->child[i]);
			}
		}
	}
}

bool query(TrieNode *root, string &input) {
	int n = input.length();
	int index;
	TrieNode *current = root;
	for (int i = 0; i < n; i++) {
		index = input[i] - 'a';
		while (current->child[index] == NULL && current != root) {
			current = current->suffix;
		}
		current = current->child[index];
		if (current != NULL && current->flag == 1) {
			return true;
		}
		if (current == NULL) {
			current = root;
		}
	}
	return false;
}

int main() {
	TrieNode *root = new TrieNode();
	int N;
	string input;
	std::cin >> N;
	while (N--) {
		std::cin >> input;
		buildTrieTree(root, input, 0);
	}
	buildAC(root);
	std::cin >> input;
	if (query(root, input)) {
		std::cout << "YES" << std::endl;
	} else {
		std::cout << "NO" << std::endl;
	}
	//system("pause");
	return 0;
}