#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
#include <string>

using namespace std;
map<string, string> fa;
map<string, int> vis;
int n, m;

void Find(string a, string b) {
	vis.clear();
	string x = a;
	while (!x.empty()) { vis[x] = 1; x = fa[x]; }
	x = b;
	while (!x.empty() && !vis[x]) x = fa[x];
	if (!x.empty()) cout << x << "\n";
	else cout << "-1\n";
}

int main() {
	string a, b;
	scanf("%d", &n);
	fa.clear();
	for (int i = 0; i<n; i++) {
		cin >> a >> b;
		fa[b] = a;
	}
	scanf("%d", &m);
	while (m--) {
		cin >> a >> b;
		Find(a, b);
	}
	return 0;
}