#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <climits>
#define random(x) (rand()%x)

using namespace std;

struct TreeNode {
	int key;
	int weight;
	TreeNode *left;
	TreeNode *right;
	TreeNode *father;
	TreeNode(int k, int w) : key(k), weight(w), left(NULL), right(NULL), father(NULL) {}
};

TreeNode* root = NULL;

void leftRotate(TreeNode* a) {
	TreeNode* b = a->right;
	b->father = a->father;
	if (a->father != NULL) {
		if (a->father->left == a) {
			a->father->left = b;
		} else {
			a->father->right = b;
		}
	}
	a->right = b->left;
	if (b->left != NULL) {
		b->left->father = a;
	}
	b->left = a;
	a->father = b;
}

void rightRotate(TreeNode* a) {
	TreeNode* b = a->left;
	b->father = a->father;
	if (a->father != NULL) {
		if (a->father->left == a) {
			a->father->left = b;
		} else {
			a->father->right = b;
		}
	} 
	a->left = b->right;
	if (b->right != NULL) {
		b->right->father = a;
	}
	b->right = a;
	a->father = b;
}

TreeNode* insert(TreeNode* cur, int key) {
	if (key < cur->key) {
		if (cur->left == NULL) {
			cur->left = new TreeNode(key, random(100005));
			cur->left->father = cur;
			return cur->left;
		}
		else {
			return insert(cur->left, key);
		}
	} else {
		if (cur->right == NULL) {
			cur->right = new TreeNode(key, random(100005));
			cur->right->father = cur;
			return cur->right;
		}
		else {
			return insert(cur->right, key);
		}
	}
}

void rotate(TreeNode* node) {
	while (node->father != NULL) {
		TreeNode* fa = node->father;
		if (node->weight < fa->weight) {
			if (node == fa->left) {
				rightRotate(fa);
			}
			else {
				leftRotate(fa);
			}
		} else {
			break;
		}
	}
	if (node->father == NULL) {
		root = node;
	}
	return;
}

void query(TreeNode* node, int key, int &res) {
	if (node == NULL) {
		return;
	}
	if (key < node->key) {
		if (node->left == NULL) {
			return;
		}
		return query(node->left, key, res);
	} else if (key > node->key) {
		res = max(node->key, res);
		if (node->right == NULL) {
			return;
		}
		return query(node->right, key, res);
	} else {
		res = key;
		return;
	}
}

int main() {
	int n;
	//ifstream cin("input.txt");
	//ofstream cout("output.txt");
	std::cin >> n;
	while (n--) {
		char c;
		int k;
		std::cin >> c;
		std::cin >> k;
		if (c == 'I') {
			if (root == NULL) {
				root = new TreeNode(k, random(100005));
			} else {
				TreeNode* node = insert(root, k);
				rotate(node);
			}
		}
		if (c == 'Q') {
			int res = INT_MIN;
			query(root, k, res);
			std::cout << res << endl;
		}
	}
	return 0;
}