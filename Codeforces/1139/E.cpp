#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e4 + 41, M = 2e4 + 42, INF = 0x3f3f3f3f;

struct edge {
	int to, next;
} e[M << 1];
int head[N], cnt = 1;
void ad(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int mat[N], v[N];
bool dfs(int x, int t) {
	if (x[v] == t) return false;
	x[v] = t;
	for (int i = x[head], nx; i; i = e[i].next)
		if (!(nx = e[i].to)[mat] || dfs(nx[mat], t)) return nx[mat] = x;
	return false;
}

#define X(x) ((x) + n + 1)
#define Y(x) (x)
int n, m, q, a[N], b[N], c[N], ans[N], mex, t;
bool f[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) scanf("%d", b + i);
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) scanf("%d", c + i), c[i][f] = true;
	for (int i = 1; i <= n; i++)
		if (!i[f]) ad(X(a[i]), Y(b[i]));
	for (int i = q; i >= 1; i--) {
		while (dfs(X(mex), ++t)) mex++;
		ans[i] = mex;
		ad(X(c[i][a]), Y(c[i][b]));
	}
	for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
}