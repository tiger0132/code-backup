#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long L;
const int N = 44;

int w[N][N];
char s[N];
int n;

L f[N][N][N], g[N][N][N][N], h[N][N][N];

L dfs0(int l, int r, int i);
L dfs1(int l, int r, int k, int p) {
	if (~g[l][r][k][p]) return g[l][r][k][p];
	L ret = 0;
	for (int x = k; x < p; x++) ret += dfs0(l, x, k) * dfs0(x + 1, r, p);
	return g[l][r][k][p] = ret;
}
L dfs2(int l, int r, int p) {
	if (~h[l][r][p]) return h[l][r][p];
	L ret = 0;
	for (int x = l; x <= r; x++)
		if (w[x][p]) ret += dfs0(l, r, x);
	return h[l][r][p] = ret;
}
L dfs0(int l, int r, int p) {
	if (l == r) return 1;
	if (l == p || r == p) return 0;
	if (~f[l][r][p]) return f[l][r][p];
	L ret = 0;
	for (int x = l; x < p; x++)
		for (int y = r; y > p; y--) ret += dfs2(l, x, y) * dfs1(x + 1, r, p, y);
	f[l][r][p] = ret;
	return ret;
}

L ans;
int main() {
	memset(f, -1, sizeof f);
	memset(g, -1, sizeof g);
	memset(h, -1, sizeof h);
	scanf("%d", &n);
	for (int i = 1; i <= n * 2; i++) {
		scanf("%s", s + 1);
		for (int j = 1; j <= n * 2; j++) w[i][j] = s[j] - '0';
	}
	for (int i = 2; i <= n * 2; i++)
		if (w[1][i]) ans += dfs0(2, n * 2, i);
	printf("%lld\n", ans);
}
