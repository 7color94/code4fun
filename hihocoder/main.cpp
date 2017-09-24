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
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <stack>
using namespace std;

struct op {
    int c; // 0, 1
    char oo;
    int num;
} ops[110];

int calculator(int lo, int hi) {
    stack<op> pp;
    stack<char> cc;
    int i = lo;
    while (i < hi) {
        if (ops[i].c == 0) {
            pp.push(ops[i]);
            i++;
        } else {
            if (ops[i].oo == '(') {
                int j = i + 1;
                int zz = 0;
                while (j < hi) {
                    if (ops[j].c == 1 && ops[j].oo == '(') zz++;
                    if (ops[j].c == 1 && ops[j].oo == ')') {
                        if (zz == 0) break;
                        else zz--;
                    }
                    j++;
                }
                int ans = calculator(i + 1, j);
                op oopp = {0, ' ', ans};
                pp.push(oopp);
                i = j + 1;
            } else if (ops[i].oo == '+' || ops[i].oo == '-' || ops[i].oo == '*' || ops[i].oo == '/') {
                if (cc.size() != 0) {
                    while (!cc.empty()) {
                        char last_op = cc.top();
                        if (last_op == '*' || last_op == '/') {
                            op t1 = pp.top(); pp.pop();
                            op t3 = pp.top(); pp.pop();
                            char t2 = cc.top(); cc.pop();
                            int ans = 0;
                            if (t2 == '*') ans = t3.num * t1.num;
                            else ans = t3.num / t1.num;
                            op oopp = {0, ' ', ans};
                            pp.push(oopp);
                        } else {
                            if (ops[i].oo == '*' || ops[i].oo == '/') {
                                break;
                            } else {
                                op t1 = pp.top(); pp.pop();
                                op t3 = pp.top(); pp.pop();
                                char t2 = cc.top(); cc.pop();
                                int ans = 0;
                                if (t2 == '+') ans = t3.num + t1.num;
                                else ans = t3.num - t1.num;
                                op oopp = {0, ' ', ans};
                                pp.push(oopp);
                            }
                        }
                    }
                }
                cc.push(ops[i].oo);
                i++;
            }
        }
    }
    while (!cc.empty() && !pp.empty() && pp.size() != 1) {
        op t1 = pp.top(); pp.pop();
        op t3 = pp.top(); pp.pop();
        char t2 = cc.top(); cc.pop();
        int ans = 0;
        if (t2 == '*') ans = t3.num * t1.num;
        else if (t2 == '/') ans = t3.num / t1.num;
        else if (t2 == '+') ans = t3.num + t1.num;
        else ans = t3.num - t1.num;
        op oopp = {0, ' ', ans};
        pp.push(oopp);
    }
    op t1 = pp.top(); pp.pop();
    return t1.num;
}

int main() {
    freopen("in.txt", "r", stdin);
    char str[100];
    scanf("%s", str);
    int i = 0, cnt = 0;
    while (i < strlen(str)) {
        if (str[i] >= '0' && str[i] <= '9') {
            string t = "";
            int j = i;
            for ( ; j < strlen(str); j++) {
                if (str[j] >= '0' && str[j] <= '9') {
                    t += str[j];
                } else {
                    break;
                }
            }
            i = j;
            ops[cnt].c = 0;
            ops[cnt].num = atoi(t.c_str());
            ops[cnt++].oo = ' ';
        } else {
            ops[cnt].c = 1;
            ops[cnt].num = 0;
            ops[cnt++].oo = str[i++];
        }
    }
    int ans = calculator(0, cnt);
    printf("%d\n", ans);
    return 0;
}