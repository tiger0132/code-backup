#include <algorithm>
#include <cstdio>
#ifdef TIGER0132
#define DBG(...) DBG(__VA_ARGS__)
#else
#define DBG(...)
#endif

const int N = 2e4 + 42;
struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, x[head], z}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head], z}, y[head] = cnt;
}

int par[N], dep[N], sz[N], son[N];
int c[3], ans;
void dfs1(int x, int p, int d) {
	x[par] = p, x[dep] = d, x[sz] = 1;
	for (int i = x[head], nx, mx = 0; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs1(nx, x, d + e[i].w), x[sz] += nx[sz];
			if (nx[sz] > mx) mx = nx[sz], x[son] = nx;
		}
}
void add(int x, int ofs) {
	(x[dep] % 3)[c] += ofs;
	if (ofs == 1)
		DBG("ADD %d[%d]\n", x, x[dep] % 3);
	else
		DBG("DEL %d[%d]\n", x, x[dep] % 3);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par]) add(nx, ofs);
}
void calc(int x, int t) {
	int p = x[dep] % 3, q = ((2 * t[dep] - x[dep]) % 3 + 3) % 3;
	DBG("x = %d, t = %d, (%d)(%d): [%d]\n", x, t, p, q, q[c]);
	ans += q[c];
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par]) calc(nx, t);
}
void dfs2(int x, bool f) {
	DBG("[%d] BEGIN\n", x);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par] && nx != x[son]) dfs2(nx, false);
	if (x[son]) dfs2(x[son], true);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par] && nx != x[son]) calc(nx, x), add(nx, 1);
	ans += (x[dep] % 3)[c];
	(x[dep] % 3)[c]++;
	DBG("ADD %d[%d]\n", x, x[dep] % 3);
	if (!f) add(x, -1);
	// DBG("[%d][%d][%d] %d\n", c[0], c[1], c[2], ans);
	DBG("[%d] END (%d)\n", x, ans);
}

int n, x, y, z;
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) scanf("%d%d%d", &x, &y, &z), addedge(x, y, z);
	dfs1(1, 0, 0), dfs2(1, true);
	ans = ans * 2 + n;
	x = std::__gcd(ans, n * n);
	printf("%d/%d", ans / x, n * n / x);
}