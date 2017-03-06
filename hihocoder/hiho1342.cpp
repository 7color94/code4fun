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

struct TreeNode {
	long px, py;
	TreeNode* left;
	TreeNode* right;
	TreeNode(long x, long y) : px(x), py(y),left(NULL), right(NULL) {}
};

int calStep(int height) {
	if (height == 1) {
		return 0;
	}
	if (height == 2) {
		return 1;
	}
	if (height == 3) {
		return 2;
	}
	return calStep(height - 1) * 2 + 1;
}

void buildTree(TreeNode* node, int height) {
	if (height == 1) {
		return;
	}
	int step = calStep(height);
	TreeNode* leftChild = new TreeNode(node->px + step + 1, node->py - step - 1);
	TreeNode* rightChild = new TreeNode(node->px + step + 1, node->py + step + 1);
	node->left = leftChild;
	node->right = rightChild;
	buildTree(node->left, height - 1);
	buildTree(node->right, height - 1);
}

int countNode(TreeNode* node, int x1, int y1, int x2, int y2) {
	if (node == NULL) {
		return 0;
	}
	if (node->px >= x1 && node->px <= x2 && node->py >= y1 && node->py <= y2) {
		return 1 + countNode(node->left, x1, y1, x2, y2) + countNode(node->right, x1, y1, x2, y2);
	} else {
		return countNode(node->left, x1, y1, x2, y2) + countNode(node->right, x1, y1, x2, y2);
	}
}

int main() {
	//ifstream cin("input.txt");
	//ofstream cout("output.txt");
	int n, m;
	cin >> n;
	cin >> m;
	TreeNode* root = new TreeNode(0, 0);
	buildTree(root, n);
	while (m--) {
		int x1, y1, x2, y2;
		cin >> x1;
		cin >> y1;
		cin >> x2;
		cin >> y2;
		int num = countNode(root, x1, y1, x2, y2);
		cout << num << endl;
	}
	return 0;
}