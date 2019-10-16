#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e5 + 51;
struct edge {
	int to, next;
} e[N << 1];
int head[N], d[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt, x[d]++;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt, y[d]++;
}

int n, c[4][N], col[N], vis[N], ord[N], idx;
void dfs(int x) {
	x[vis] = 1, ord[++idx] = x;
	for (int i = x[head], nx; i; i = e[i].next)
		if (!(nx = e[i].to)[vis]) dfs(nx);
}

ll ans = 1e18, t;
int x0, y0;
void calc(int x, int y) {
	ll r = ord[1][c[ord[1][col] = x]] + ord[2][c[ord[2][col] = y]];
	int tx = x, ty = y;
	for (int i = 3, j = x ^ y; i <= n; i++, x = y, y = j, j = x ^ y)
		r += ord[i][c[ord[i][col] = j]];
	if (r < ans) ans = r, x0 = tx, y0 = ty;
}

int s, x, y, v[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", c[1] + i);
	for (int i = 1; i <= n; i++) scanf("%d", c[2] + i);
	for (int i = 1; i <= n; i++) scanf("%d", c[3] + i);
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	for (int i = 1; i <= n; i++) {
		if (i[d] == 1) s = i;
		if (i[d] > 2) return puts("-1"), 0;
	}
	dfs(s), calc(1, 2), calc(2, 1), calc(2, 3), calc(3, 2), calc(1, 3), calc(3, 1);
	printf("%lld\n", ans), calc(x0, y0);
	for (int i = 1; i <= n; i++) printf("%d%c", i[col], " \n"[i == n]);
}