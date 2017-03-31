#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<stack>

using namespace std;

#define swap(x, t, y) (t = x, x = y, y = t)//交换x和y

int a[1111111], k;

int find(int s, int e)//快排思想
{
	if (s == e && a[s] != k)
		return -1;
	int i = s - 1, j, t, r, x = a[e];
	for (j = s; j < e; j++)
	{
		if (a[j] <= x)
		{
			i++;
			swap(a[i], t, a[j]);
		}
	}
	swap(a[i + 1], t, a[e]);
	if (a[i + 1] < k)
	{
		r = rand() % (e - i - 1) + i + 2;//随机选择a[r]作为主元
		swap(a[r], t, a[e]);
		find(i + 2, e);
	}
	else if (a[i + 1] > k)
	{
		r = rand() % (i + 1 - s) + s;
		swap(a[r], t, a[i]);
		find(s, i);
	}
	else
		return i + 1;
}

int main(void)
{
	int i, n, r, t;
	cin >> n >> k;
	for (i = 1; i <= n; i++)
		cin >> a[i];
	r = rand() % n + 1;
	swap(a[r], t, a[n]);
	cout << find(1, n) << endl;
	//system("pause");
}