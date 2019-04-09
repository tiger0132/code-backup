// WRONG ANSWER

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <numeric>

const double eps = 1e-6;
const int N = 1e2 + 21;

int gauss(int n, double a[][N], double *ans) {
	bool f1 = false, f2 = false;
	for (int i = 1; i <= n; i++) {
		int pos = i;
		for (int j = i + 1; j <= n; j++)
			if (fabs(a[j][i]) > fabs(a[pos][i])) pos = j;
		if (fabs(a[pos][i]) < eps) continue;
		std::swap(a[i], a[pos]);
		double tmp = a[i][i];
		for (int j = i; j <= n + 1; j++) a[i][j] /= tmp;
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			tmp = a[j][i];
			for (int k = i; k <= n + 1; k++) a[j][k] -= a[i][k] * tmp;
		}
	}
	for (int i = 1; i <= n; i++) {
		int cnt = std::accumulate(a[i] + 1, a[i] + n + 2, 0, [](int x, double y) { return x + (fabs(y) < eps); });
		if (cnt == n && fabs(a[i][n + 1]) > eps) f1 = true;
		if (cnt == n + 1) f2 = true;
	}
	for (int i = 1; i <= n; i++) ans[i] = a[i][n + 1];
	return f1 ? -1 : f2 ? 0 : 1;
}
double a[N][N], b[N];
int n, ret;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n + 1; j++) scanf("%lf", a[i] + j);
	}
	if ((ret = gauss(n, a, b)) <= 0) return !printf("%d", ret);
	for (int i = 1; i <= n; i++) {
		if (fabs(b[i]) < eps)
			printf("x%d=0\n", i);
		else
			printf("x%d=%.2f\n", i, b[i]);
	}
}