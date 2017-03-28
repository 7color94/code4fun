#include<iostream>
#include<vector>
#include<fstream>
#include<math.h>

using namespace std;

#define MAXN 500 + 5
#define MAXM 500 * 2 + 5

int N, M;
double A[MAXM][MAXN];
double b[MAXM];
int value[MAXN];

bool manySolutionFlag = false;
bool noSolutionFlag = false;

const double eps = 1e-6;

bool is_zero(double x) {
	return fabs(x) < eps;
}

void swap_row(int x, int y) {
	if (x != y) {
		for (int i = 1; i <= N; i++) {
			std::swap(A[x][i], A[y][i]);
		}
	}
}

void Gaussian_elimination() {
	for (int i = 1; i <= N; i++) {
		bool flag = false;
		// j从第i行开始，找到第i行不等于0的j
		for (int j = i; j <= M; j++) {
			if (A[j][i] != 0) {
				swap_row(i, j);
				flag = true;
				break;
			}
		}
		if (!flag) {
			manySolutionFlag = true;
			return;
		}
		for (int j = i + 1; j <= M; j++) {
			double f = 1.0 * A[j][i] / A[i][i];
			for (int t = i; t <= N; t++) {
				A[j][t] = A[j][t] - A[i][t] * f;
			}
			b[j] = b[j] - b[i] * f;
		}
	}
}

void cal_solution() {
	Gaussian_elimination();
	for (int i = 1; i <= M; i++) {
		bool flag = true;
		for (int j = 1; j <= N; j++) {
			if (!is_zero(A[i][j])) {
				flag = false;
			}
		}
		if (flag && is_zero(b[i])) {
			flag = false;
		}
		if (flag) {
			noSolutionFlag = true;
			return;
		}
	}
	for (int i = N; i >= 1; i--) {
		for (int j = i + 1; j <= N; j++) {
			b[i] = b[i] - A[i][j] * value[j];
			A[i][j] = 0;
		}
		value[i] = b[i] / A[i][i] + 0.5;
	}
}

int main() {
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	cin >> N;
	cin >> M;
	int _a, _b;
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> _a;
			A[i][j] = _a;
		}
		cin >> _b;
		b[i] = _b;
	}
	cal_solution();
	if (noSolutionFlag) {
		cout << "No solutions" << endl;
	}
	else if (manySolutionFlag) {
		cout << "Many solutions" << endl;
	}
	else {
		for (int i = 1; i <= N; i++) {
			cout << value[i] << endl;
		}
	}
	return 0;
}