#include<iostream>
#include<string.h>

using namespace std;




int main() {
    int childs[3005], f[3005], n;
    std::cin >> n;
    memset(childs, 0, sizeof(childs));
//    for (int i = 0; i < 3005; i++) {
//        childs[i] = 0;
//    }
    int father;
    for (int i = 1; i < n; i++) {
        std::cin >> father;
        childs[father]++;
    }
//    for (int i = 0; i < 3005; i++) {
//        f[i] = 100000;
//    }
    memset(f, 100000, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = n-1; j >= childs[i]; j--) {
            f[j] = min(f[j], f[j-childs[i]]+1);
        }
    }
    for (int i = 0; i < n - 1; i++) {
        if (f[i] >= 100000) {
            f[i] = -1;
        }
        std::cout << f[i] << " ";
    }
    if (f[n-1] >= 100000) {
        f[n-1] = -1;
    }
    std::cout << f[n-1] << std::endl;
}
