#include<iostream>
#include<algorithm>

using namespace std;

const int row = 5;
const int col = 6;
const int MAXN = row * col;

int y[MAXN + 1] = { 0 };
int A[MAXN + 1][MAXN + 1] = {0};
int value[MAXN + 1] = { 0 };
int dirs[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
int ans = 0;

bool manySolutionFlag = false;
bool noSolutionFlag = false;

void swap_row(int ii, int jj) {
	if (ii != jj) {
		for (int i = 1; i <= MAXN; i++) {
			std::swap(A[ii][i], A[jj][i]);
		}
		std::swap(y[ii], y[jj]);
	}
}

void Gaussian_elimination() {
	for (int i = 1; i <= MAXN; i++) {
		for (int j = i; j <= MAXN; j++) {
			if (A[j][i] == 1) {
				swap_row(i, j);
				break;
			}
		}
		for (int j = i + 1; j <= MAXN; j++) {
			if (A[j][i] == 1) {
				for (int t = i; t <= MAXN; t++) {
					A[j][t] = A[j][t] ^ A[i][t];
				}
				y[j] = y[j] ^ y[i];
			}
		}
	}
}

void cal_solution() {
	Gaussian_elimination();
	/*
	for (int i = MAXN; i >= 1; i--) {
		int sum = 0;
		for (int j = i + 1; j <= MAXN; j++) {
			sum ^= A[i][j] * value[j];
		}
		value[i] = (y[i] ^ sum) / A[i][i];
		if (value[i] == 1) {
			ans++;
		}
	}
	*/
	
	ans = 0;
	value[MAXN] = y[MAXN];
	if (value[MAXN] == 1) {
		ans += 1;
	}
	for (int i = MAXN - 1; i >= 1; i--) {
		int _x = A[i][i + 1] * value[i + 1];
		for (int j = i + 2; j <= MAXN; j++) {
			_x ^= (A[i][j] * value[j]);
		}
		value[i] = _x ^ y[i];
		if (value[i] == 1) {
			ans += 1;
		}
	}
	
}

int main() {
	char ch;
	memset(y, 0, sizeof(y));
	memset(A, 0, sizeof(A));
	memset(value, 0, sizeof(value));
	for (int i = 1; i <= MAXN; i++) {
		do {
			ch = getchar();
		} while ((ch < '0' || ch > '1'));
		if (ch == '1') {
			y[i] = 0;
		} else {
			y[i] = 1;
		}
	}

	// cal A
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			int idx = (i - 1) * col + j;
			A[idx][idx] = 1;
			for (int d = 0; d < 4; d++) {
				int x = i + dirs[d][0];
				int y = j + dirs[d][1];
				if (x >= 1 && x <= row && y >= 1 && y <= col) {
					int _idx = (x - 1) * col + y;
					A[idx][_idx] = 1;
				}
			}
		}
	}

	cal_solution();
	
	printf("%d\n", ans);
	for (int i = 1; i <= MAXN; i++) {
		if (value[i] == 1) {
			printf("%d %d\n", 1 + (i - 1) / col, 1 + (i - 1) % col);
		}
	}

	return 0;
}