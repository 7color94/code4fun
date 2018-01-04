#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

struct TreeNode {
    int id, val, num;
    long long totalVal, lazy;
    TreeNode *left;
    TreeNode *right;
    TreeNode *father;
    TreeNode(int id, int val): id(id), val(val), totalVal(0), num(0), lazy(0), left(NULL), right(NULL), father(NULL) {}
};

TreeNode *root = NULL;

void update(TreeNode *x) {
    if (x->id != -1 && x->id != 1e8+1) x->num = 1;
    x->totalVal = x->val;
    if (x->left != NULL) {
        x->num = x->num + x->left->num;
        x->totalVal = x->totalVal + x->left->totalVal;
    }
    if (x->right != NULL) {
        x->num = x->num + x->right->num;
        x->totalVal = x->totalVal + x->right->totalVal;
    }
}

void markLazyTag(TreeNode *node, int delta) {
    node->lazy = node->lazy + delta;
    node->totalVal = node->totalVal + node->num * delta;
    if (node->id != -1 && node->id != 1e8+1) node->val = node->val + delta;
}

void sendLazyTag(TreeNode *node) {
    if (node->left != NULL) markLazyTag(node->left, node->lazy);
    if (node->right != NULL) markLazyTag(node->right, node->lazy);
    node->lazy = 0;
    update(node);
}

void leftRotate(TreeNode *x) {
    TreeNode *p = x->father;
    sendLazyTag(p);
    sendLazyTag(x);
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
    update(p);
    update(x);
}

void rightRotate(TreeNode *x) {
    TreeNode *p = x->father;
    sendLazyTag(p);
    sendLazyTag(x);
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
    update(p);
    update(x);
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

TreeNode* bst_insert(TreeNode *cur, int id, int val) {
    sendLazyTag(cur);
    if (id < cur->id) {
        if (cur->left == NULL) {
            cur->left = new TreeNode(id, val);
            cur->left->father = cur;
            update(cur->left);
        } else {
            bst_insert(cur->left, id, val);
        }
    } else if (id > cur->id) {
        if (cur->right == NULL) {
            cur->right = new TreeNode(id, val);
            cur->right->father = cur;
            update(cur->right);
        } else {
           bst_insert(cur->right, id, val);
        }
    } else {
        // do nothing
    }
    update(cur);
    return cur;
}

TreeNode* insert(int id, int val) {
    if (root == NULL) {
        root = new TreeNode(id, val);
    } else {
        TreeNode *node = bst_insert(root, id, val);
        splay(node, NULL);
    }
}

TreeNode* find(TreeNode *node, int id) {
    if (node == NULL) return NULL;
    if (id < node->id) {
        if (node->left == NULL) return NULL;
        return find(node->left, id);
    } else if (id > node->id) {
        if (node->right == NULL) return NULL;
        return find(node->right, id);
    } else {
        return node;
    }
}

TreeNode* findPrev(int id) {
    splay(find(root, id), NULL);
    TreeNode *node = root->left;
    while (node->right != NULL) node = node->right;
    return node;
}

TreeNode* findNext(int id) {
    splay(find(root, id), NULL);
    TreeNode *node = root->right;
    while(node->left != NULL) node = node->left;
    return node;
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

void deleteKey(int id) {
    TreeNode *prev = findPrev(id);
    TreeNode *next = findNext(id);
    splay(prev, NULL);
    splay(next, prev);
    TreeNode *to_delete = next->left;
    next->left = NULL;
    update(next);
    update(prev);
    deleteNode(to_delete);
}

long long queryInterval(int a, int b) {
    int a_exist = 0, b_exist = 0;
    TreeNode *node_a = find(root, a);
    TreeNode *node_b = find(root, b);
    if (node_a == NULL) insert(a, 0);
    else a_exist = 1;
    if (node_b == NULL) insert(b, 0);
    else b_exist = 1;

    TreeNode *prev = findPrev(a);
    TreeNode *next = findNext(b);
    splay(prev, NULL);
    splay(next, prev);
    long long ans = next->left->totalVal;

    if (a_exist == 0) deleteKey(a);
    if (b_exist == 0) deleteKey(b);
    return ans;
}

void modifyInterval(int a, int b, int delta) {
    int a_exist = 0, b_exist = 0;
    TreeNode *node_a = find(root, a);
    TreeNode *node_b = find(root, b);
    if (node_a == NULL) insert(a, 0);
    else a_exist = 1;
    if (node_b == NULL) insert(b, 0);
    else b_exist = 1;

    TreeNode *prev = findPrev(a);
    TreeNode *next = findNext(b);
    splay(prev, NULL);
    splay(next, prev);
    markLazyTag(next->left, delta);

    if (a_exist == 0) deleteKey(a);
    if (b_exist == 0) deleteKey(b);
}

void delelteInterval(int a, int b) {
    insert(a, 0);
    insert(b, 0);
    TreeNode *prev = findPrev(a);
    TreeNode *next = findNext(b);
    splay(prev, NULL);
    splay(next, prev);
    TreeNode *to_delete = next->left;
    next->left = NULL;
    update(next);
    update(prev);
    deleteNode(to_delete);
}

int main() {
    // freopen("in.txt", "r", stdin);
    ifstream cin("in.txt");
    int n;
    cin >> n;
    char c;
    int id, val, a, b, delta;
    insert(-1, 0);
    insert(1e8+1, 0);
    while (n--) {
        cin >> c;
        if (c == 'I') {
            cin >> id >> val;
            insert(id, val);
        } else if (c == 'Q') {
            cin >> a >> b;
            long long ans =  queryInterval(a, b);
            cout << ans << endl;
        } else if (c == 'M') {
            cin >> a >> b >> delta;
            modifyInterval(a, b, delta);
        } else {
            cin >> a >> b;
            delelteInterval(a, b);
        }
    }
    return 0;
}