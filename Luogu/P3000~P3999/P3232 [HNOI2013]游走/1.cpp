#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>

const int N = 5e2 + 25, M = 3e5 + 53;
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

double a[N][N], b[N], e[M], ans;
int n, m, x[M], y[M], deg[N];
int main() {
	scanf("%d%d", &n, &m), a[1][n] = 1;
	for (int i = 1; i <= m; i++) scanf("%d%d", x + i, y + i), deg[x[i]]++, deg[y[i]]++;
	for (int i = 1; i <= n - 1; i++) a[i][i] = 1;
	for (int i = 1; i <= m; i++)
		if (x[i] < n && y[i] < n) a[x[i]][y[i]] = -1. / deg[y[i]], a[y[i]][x[i]] = -1. / deg[x[i]];
	gauss(n - 1, a, b);
	for (int i = 1; i <= m; i++) {
		if (x[i] != n) e[i] += b[x[i]] / deg[x[i]];
		if (y[i] != n) e[i] += b[y[i]] / deg[y[i]];
	}
	std::sort(e + 1, e + m + 1, std::greater<double>());
	for (int i = 1; i <= m; i++) ans += e[i] * i;
	printf("%.3f", ans);
}