#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const double eps = 1e-6;
const int N = 1e2 + 21;

bool gauss(int n, double a[][N], double *ans) {
	for (int i = 1; i <= n; i++) {
		int pos = i;
		for (int j = i + 1; j <= n; j++)
			if (fabs(a[j][i]) > fabs(a[pos][i])) pos = j;
		if (fabs(a[pos][i]) < eps) return false;
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
	return true;
}
double a[N][N], b[N];
int n;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n + 1; j++) scanf("%lf", a[i] + j);
	}
	if (!gauss(n, a, b)) return puts("No Solution"), 0;
	for (int i = 1; i <= n; i++) printf("%.2f\n", b[i]);
}