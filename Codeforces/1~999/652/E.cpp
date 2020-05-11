#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
#include <utility>
#include <vector>

typedef std::pair<int, int> pii;
const int N = 3e5 + 53;
struct edge {
	int to, next, w, f;
} e[N << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, x[head], z, 0}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head], z, 0}, y[head] = cnt;
}

int dfn[N], low[N], vis[N], col[N], has1[N], idx, dc;
void dfs(int x, int p) {
	x[dfn] = x[low] = ++idx, x[vis] = 1;
	for (int i = x[head], nx; i; i = e[i].next)
		if (!(nx = e[i].to)[vis]) {
			dfs(nx, i);
			x[low] = std::min(x[low], nx[low]);
			if (nx[low] > x[dfn]) e[i].f = e[i ^ 1].f = 1;
		} else if (i != (p ^ 1))
			x[low] = std::min(x[low], nx[dfn]);
}
void dfs2(int x, int c) {
	x[col] = c;
	for (int i = x[head], nx; i; i = e[i].next)
		if (!e[i].f && !(nx = e[i].to)[col]) dfs2(nx, c);
}

int s, t;
bool dfs3(int x, int f) {
	x[vis] = 1, f |= x[has1];
	if (x == t) return f;
	for (int i = x[head]; i; i = e[i].next)
		if (!e[i].to[vis] && dfs3(e[i].to, f | e[i].w)) return true;
	return false;
}

int n, m, x[N], y[N], z[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", x + i, y + i, z + i), addedge(x[i], y[i], z[i]);
	for (int i = 1; i <= n; i++)
		if (!i[dfn]) dfs(i, -1);
	for (int i = 1; i <= n; i++)
		if (!i[col]) dfs2(i, ++dc);
	memset(head, 0, sizeof head), cnt = 0;
	for (int i = 1; i <= m; i++)
		if (x[i][col] != y[i][col])
			addedge(x[i][col], y[i][col], z[i]);
		else
			x[i][col][has1] |= z[i];
	memset(vis, 0, sizeof vis);
	scanf("%d%d", &s, &t), s = s[col], t = t[col];
	puts(dfs3(s, 0) ? "YES" : "NO");
}