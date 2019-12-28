#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

struct edge {
	int to, next, f, id;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int id) {
	e[++cnt] = {y, x[head], 1, id}, x[head] = cnt;
	e[++cnt] = {x, y[head], -1, id}, y[head] = cnt;
}

int p[N];
int f(int x) { return p[x] ? p[x] = f(p[x]) : x; }
void $(int x, int y) {
	if ((x = f(x)) != (y = f(y))) x[p] = y;
}

int n, a[N], m, x, y, s[N], ans[N];
void dfs(int x, int p) {
	x[s] = x[a];
	for (int i = head[x], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs(nx, x);
			ans[e[i].id] = e[i].f * nx[s];
			x[s] += nx[s];
		}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), x += a[i];
	if (x) return puts("Impossible"), 0;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &x, &y);
		if (f(x) ^ f(y)) $(x, y), addedge(x, y, i);
	}
	dfs(1, 0);
	puts("Possible");
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}