#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <map>
#include <set>
#include <stack>
#include <sstream>
#include <queue>
#include<functional> 
#include<sstream>	
#include<climits>
#include<unordered_set>
#include<regex>
#include <cstring>

using namespace std;

#define CHAR_RANGE 26

struct TrieNode
{
	bool flag;
	int count;
	TrieNode *childs[CHAR_RANGE];
	TrieNode *parent;
	TrieNode() :parent(NULL), flag(false), count(0) {
		for (int i = 0; i < CHAR_RANGE; i++)
			childs[i] = NULL;
	}
};
void insertWord(TrieNode *p, char* word)
{
	if ((*word) == '\0')
	{
		p->flag = true;
		return;
	}
	int index = word[0] - 'a';
	if (p->childs[index] == NULL)
		p->childs[index] = new TrieNode();
	if (p->childs[index]->parent == NULL)
		p->childs[index]->parent = p;
	p->childs[index]->count++;
	insertWord(p->childs[index], word + 1);
}
int findPrefix(TrieNode *p, char* word)
{
	if ((*word) == '\0')
	{
		return p->count;
	}
	int index = word[0] - 'a';
	if (p->childs[index] == NULL)
		return 0;
	return findPrefix(p->childs[index], word + 1);
}
int main() {
	int n, m;
	string input;
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	cin >> n;
	char tmp[20];
	TrieNode *tree = new TrieNode();
	for (int i = 0; i < n; i++)
	{
		cin >> input;
		strcpy(tmp, input.c_str());
		insertWord(tree, tmp);
	}
	cin >> m;
	int num;
	for (int i = 0; i < m; i++)
	{
		cin >> input;
		strcpy(tmp, input.c_str());
		num = findPrefix(tree, tmp);
		cout << num << endl;
	}
	return 0;
}