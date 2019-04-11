#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 3e2 + 23, M = 5e4 + 45;
void gauss(int n, double a[][N], double *ans) {
	for (int i = 1; i <= n; i++) {
		int pos = i;
		for (int j = i + 1; j <= n; j++)
			if (fabs(a[j][i]) > fabs(a[pos][i])) pos = j;
		std::swap(a[i], a[pos]);
		double tmp = a[i][i];
		for (int j = i; j <= n + 1; j++) a[i][j] /= tmp;
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			tmp = a[j][i];
			for (int k = i; k <= n + 1; k++) a[j][k] -= a[i][k] * tmp;
		}
	}
	for (int i = 1; i <= n; i++) ans[i] = a[i][n + 1];
}

double a[N][N], b[N], t;
int n, m, p, q, x, y;
int deg[N], g[N][N];
int main() {
	for (scanf("%d%d%d%d", &n, &m, &p, &q); m--;) {
		scanf("%d%d", &x, &y), g[x][y] = g[y][x] = 1, deg[x]++, deg[y]++;
	}
	t = 1. * p / q;
	for (int i = 1; i <= n; i++) {
		a[i][i] = 1;
		for (int j = 1; j <= n; j++) {
			if (g[i][j]) a[i][j] -= (1. - t) / deg[j];
		}
	}
	a[1][n + 1] = 1;
	gauss(n, a, b);
	for (int i = 1; i <= n; i++) printf("%.9f\n", t * b[i]);
}