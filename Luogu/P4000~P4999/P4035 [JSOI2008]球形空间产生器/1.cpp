#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define S(x) ((x) * (x))

const int N = 22;

void gauss(int n, double a[][N], double ans[]) {
	for (int i = 1; i <= n; i++) {
		int pos = i;
		for (int j = i + 1; j <= n; j++)
			if (fabs(a[j][i]) > fabs(a[pos][i])) pos = j;
		std::swap(a[i], a[pos]);
		double tmp = a[i][i];
		for (int j = i; j <= n + 1; j++) a[i][j] /= tmp;
		for (int j = i + 1; j <= n; j++) {
			tmp = a[j][i];
			for (int k = i; k <= n + 1; k++) a[j][k] -= a[i][k] * tmp;
		}
	}
	ans[n] = a[n][n + 1];
	for (int i = n - 1; i >= 1; i--) {
		ans[i] = a[i][n + 1];
		for (int j = i + 1; j <= n; j++) ans[i] -= a[i][j] * ans[j];
	}
}

double a[N][N], b[N], last[N], x;
int n;
int main() {
	scanf("%d", &n);
	for (int i = 0; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%lf", &x);
			if (i) {
				a[i][j] = 2 * (last[j] - x);
				a[i][n + 1] += S(last[j]) - S(x);
			}
			last[j] = x;
		}
	}
	gauss(n, a, b);
	for (int i = 1; i <= n; i++) printf("%.03f ", b[i]);
}