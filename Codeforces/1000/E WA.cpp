#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 3e5 + 53;

struct edge {
	int to, next, f;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = {y, x[head]}, x[head] = cnt;
	e[++cnt] = {x, y[head]}, y[head] = cnt;
}

int dfn[N], low[N], col[N], idx, dcnt, c0;
void dfs(int x, int p) {
	x[dfn] = x[low] = ++idx;
	for (int i = x[head], nx; i; i = e[i].next)
		if (!(nx = e[i].to)[dfn]) {
			dfs(nx, x);
			x[low] = std::min(x[low], nx[low]);
			if (nx[low] > x[dfn]) e[i].f = e[i ^ 1].f = 1;
		} else if (nx != p)
			x[low] = std::min(x[low], nx[dfn]);
}
void dfs2(int x, int c) {
	x[col] = c;
	for (int i = x[head], nx; i; i = e[i].next)
		if (!e[i].f && !(nx = e[i].to)[col]) dfs2(nx, c);
}

int mx = -1, mi, c2;
void dfs3(int x, int p, int d) {
	if (d > mx) mx = d, mi = x;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs3(nx, x, d + 1);
}

int n, m, x[N], y[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d", x + i, y + i), addedge(x[i], y[i]);
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
		if (!i[col]) dfs2(i, ++dcnt);
	memset(head, 0, sizeof head), cnt = 0;
	for (int i = 1; i <= m; i++)
		if (x[i][col] != y[i][col]) addedge(x[i][col], y[i][col]);
	dfs3(1, 0, 0);
	mx = -1, dfs3(mi, 0, 0);
	printf("%d", mx);
}