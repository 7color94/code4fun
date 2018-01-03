#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>
using namespace std;

struct TreeNode {
    int key;
    TreeNode *left;
    TreeNode *right;
    TreeNode *father;
    TreeNode(int k): key(k), left(NULL), right(NULL), father(NULL) {}
};

TreeNode *root = NULL;

void leftRotate(TreeNode *x) {
    TreeNode *p = x->father;
    x->father = p->father;
    if (p->father != NULL) {
        if (p->father->left == p) p->father->left = x;
        else p->father->right = x;
    } else {
        root = x;
    }
    p->right = x->left;
    if (x -> left != NULL) x->left->father = p;
    x->left = p;
    p->father = x;
}

void rightRotate(TreeNode *x) {
    TreeNode *p = x->father;
    x->father = p->father;
    if (p->father != NULL) {
        if (p->father->left == p) p->father->left = x;
        else p->father->right = x;
    } else {
        root = x;
    }
    p->left = x->right;
    if (x->right != NULL) x->right->father = p;
    x->right = p;
    p->father = x;
}

void splay(TreeNode *x, TreeNode *y) {
    if (x == NULL) return;
    while (x->father != y) {
        TreeNode *p = x->father;
        if (p->father == y) {
            if (p->left == x) rightRotate(x);
            else leftRotate(x);
        } else {
            TreeNode *g = p->father;
            if (g->left == p) {
                if (p->left == x) {
                    rightRotate(p);
                    rightRotate(x);
                } else {
                    leftRotate(x);
                    rightRotate(x);
                }
            } else {
                if (p->right == x) {
                    leftRotate(p);
                    leftRotate(x);
                } else {
                    rightRotate(x);
                    leftRotate(x);
                }
            }
        }
    }
}

TreeNode* insert(TreeNode *cur, int key) {
    if (key < cur->key) {
        if (cur->left == NULL) {
            cur->left = new TreeNode(key);
            cur->left->father = cur;
            return cur->left;
        } else {
            return insert(cur->left, key);
        }
    } else if (key > cur->key) {
        if (cur->right == NULL) {
            cur->right = new TreeNode(key);
            cur->right->father = cur;
            return cur->right;
        } else {
            return insert(cur->right, key);
        }
    } else {
        return NULL;
    }
}

TreeNode* find(TreeNode *node, int key) {
    if (node == NULL) return NULL;
    if (key < node->key) {
        if (node->left == NULL) return NULL;
        return find(node->left, key);
    } else if (key > node->key) {
        if (node->right == NULL) return NULL;
        return find(node->right, key);
    } else {
        return node;
    }
}

TreeNode* findPrev(int key) {
    splay(find(root, key), NULL);
    TreeNode *node = root->left;
    while (node->right != NULL) node = node->right;
    return node;
}

TreeNode* findNext(int key) {
    splay(find(root, key), NULL);
    TreeNode *node = root->right;
    while(node->left != NULL) node = node->left;
    return node;
}

void query_NMK(TreeNode *node, int key, int &res) {
    if (node == NULL) return;
    if (key < node->key) {
        if (node->left == NULL) return;
        return query_NMK(node->left, key, res);
    } else if (key > node->key) {
        res = max(node->key, res);
        if (node->right == NULL) return;
        return query_NMK(node->right, key, res);
    } else {
        res = key;
        return;
    }
}

TreeNode* deleteNode(TreeNode *node) {
    if (node->left == NULL && node->right == NULL) {
        delete node;
        return NULL;
    }
    if (node->left != NULL) node->left = deleteNode(node->left);
    if (node->right != NULL) node->right = deleteNode(node->right);
    delete node;
    return NULL;
}

void deleteKey(int key) {
    TreeNode *prev = findPrev(key);
    TreeNode *next = findNext(key);
    splay(prev, NULL);
    splay(next, prev);
    TreeNode *to_delete = next->left;
    next->left = NULL;
    deleteNode(to_delete);
}

void delelteInterval(int a, int b) {
    TreeNode *prev = findPrev(a);
    TreeNode *next = findNext(b);
    // if (prev != NULL) cout << prev->key << endl;
    // if (next != NULL) cout << next->key << endl;
    splay(prev, NULL);
    splay(next, prev);
    TreeNode *to_delete = next->left;
    next->left = NULL;
    deleteNode(to_delete);
}

int main() {
    // freopen("in.txt", "r", stdin);
    ifstream cin("in.txt");
    int n;
    cin >> n;
    char c;
    int k, a, b;
    root = new TreeNode(-1);
    insert(root, 1e9+1);
    while (n--) {
        cin >> c;
        if (c == 'I') {
            cin >> k;
            TreeNode *node = insert(root, k);
            splay(node, NULL);
        } else if (c == 'Q') {
            cin >> k;
            int ans = 0;
            query_NMK(root, k, ans);
            printf("%d\n", ans);
        } else {
            cin >> a >> b;
            insert(root, a);
            insert(root, b);
            delelteInterval(a, b);
        }
    }
    return 0;
}