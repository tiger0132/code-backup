#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <set>
#define $(x) ((x) % m + 1)
#define _(x) ((x) % n + 1)

const int N = 1e3 + 31;

int n, a[2][N], b[2][N], c1, c2, s[N], m;
bool g[N][N];
void ad(int x, int y, bool f = true) {
	g[x][y] = true, (f && x == 1 && (s[++m] = y));
	g[y][x] = true, (f && y == 1 && (s[++m] = x));
}
int flp(int x, int y) {
	for (int i = 2; i <= n; i++)
		if (g[i][x] && g[i][y]) return g[x][y] = g[y][x] = false, ad(1, i, false), i;
}
void dfs(int l, int r, bool f) {
	if (l == r || _(l) == r) return;
	int t = flp(l, r);
	if (f)
		a[0][++c1] = l, b[0][c1] = r;
	else
		a[1][++c2] = 1, b[1][c2] = t;
	dfs(l, t, f), dfs(t, r, f);
}
void go(bool f) {}
int x, y;
int main() {
	scanf("%d", &n), s[m = 1] = 1;
	for (int i = 1; i <= n - 3; i++) scanf("%d%d", &x, &y), ad(x, y);
	for (int i = 1; i <= n; i++) ad(i, _(i));
	std::sort(s + 1, s + m + 1), s[m + 1] = s[1];
	for (int i = 1; i <= m; i++) dfs(s[i], s[i + 1], true);
	memset(g, 0, sizeof g), s[m = 1] = 1;
	for (int i = 1; i <= n - 3; i++) scanf("%d%d", &x, &y), ad(x, y);
	for (int i = 1; i <= n; i++) ad(i, _(i));
	std::sort(s + 1, s + m + 1), s[m + 1] = s[1];
	for (int i = 1; i <= m; i++) dfs(s[i], s[i + 1], false);
	printf("%d\n", c1 + c2);
	for (int i = 1; i <= c1; i++) printf("%d %d\n", a[0][i], b[0][i]);
	for (int i = c2; i >= 1; i--) printf("%d %d\n", a[1][i], b[1][i]);
}