#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <cstring>
#include <cmath>
#include <climits>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
using namespace std;

char str[2000000];

struct TrieNode {
    int count;
    TrieNode *childs[26];
    TrieNode(): count(0) {
        for (int i = 0; i < 26; i++) childs[i] = NULL;
    }
};

void insertWord(TrieNode* p, char* word, int pos) {
    if (word[pos] == '\0') return;
    int index = word[pos] - 'a';
    if (p->childs[index] == NULL) p->childs[index] = new TrieNode();
    p->childs[index]->count++;
    insertWord(p->childs[index], word, pos + 1);
}

void solve(TrieNode* p, int& ans) {
    if (p == NULL) return;
    if (p->count <= 5 && p->count > 0) {
        ans++;
        return;
    }
    for (int index = 0; index < 26; index++) solve(p->childs[index], ans);
}

int main() {
    // ifstream cin("in.txt");
    freopen("in.txt", "r", stdin);
    
    int N;
    scanf("%d", &N);

    TrieNode *root = new TrieNode();

    while (N--) {
        //getchar();
        scanf("%s", str);
        insertWord(root, str, 0);
    }

    int ans = 0;
    solve(root, ans);
    printf("%d\n", ans);

    return 0;
}