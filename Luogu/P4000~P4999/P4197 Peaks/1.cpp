#include <algorithm>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
const int N = 2e5 + 52, M = 5e5 + 55, SZ = 8e6 + 68, K = 1e9, LN = 20;
int ch[SZ][2], sz[SZ], nc;
int cl(int x) { return (++nc)[L] = x[L], nc[R] = x[R], nc[sz] = x[sz], nc; }
void ins(int x, int l, int r, int i) {
	if (x[sz]++, l == r) return;
	if (i <= mid) return ins(x[L] = cl(x[L]), l, mid, i);
	ins(x[R] = cl(x[R]), mid + 1, r, i);
}
int qry(int x1, int x2, int l, int r, int k) {
	if (l == r) return l;
	if (k <= x2[R][sz] - x1[R][sz]) return qry(x1[R], x2[R], mid + 1, r, k);
	return qry(x1[L], x2[L], l, mid, k - (x2[R][sz] - x1[R][sz]));
}

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

int p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void u(int x, int y) { (x = f(x)) != (y = f(y)) && (x[p] = y); }

int lb[N], rb[N], _w[N], w[N], v[N], fa[N][LN], idx;  // v: 重构树上新点的权值
void dfs(int x, int p) {
	x[lb] = ++idx, idx[w] = x[_w], x[fa][0] = p;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs(nx, x);
	x[rb] = idx;
}
int fwd(int x, int k) {
	for (int i = LN - 1; i >= 0; i--)
		if (x[fa][i][v] <= k) x = x[fa][i];
	return x;
}

int n, m, q, a, b, c, x[M], y[M], z[M], id[M], rt[N], ps[N];
int main() {
	v[0] = 2e9;
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++) scanf("%d", _w + i);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", x + i, y + i, z + i), i[id] = i;
	std::sort(id + 1, id + m + 1, [](int a, int b) { return a[z] < b[z]; });
	for (int i = 1; i <= m; i++) {
		if ((a = f(i[id][x])) != (b = f(i[id][y])))
			u(a, b), u(a, ++n), n[v] = i[id][z], addedge(n, a), addedge(n, b);
		// printf("%d -- %d [%d] -- %d\n", a, n, i[id][z], b);
	}
	dfs(n, 0);
	for (int i = 1; i <= idx; i++) {
		ins(i[rt] = cl((i - 1)[rt]), 0, K, i[w]);
		i[ps] = (i - 1)[ps] + !!i[w];
	}
	for (int j = 1; j < LN; j++)
		for (int i = 1; i <= n; i++) i[fa][j] = i[fa][j - 1][fa][j - 1];
	while (q--) {
		scanf("%d%d%d", &a, &b, &c);
		a = fwd(a, b);
		printf("%d\n", a[rb][ps] - (a[lb] - 1)[ps] < c
						   ? -1
						   : qry((a[lb] - 1)[rt], a[rb][rt], 0, K, c));
	}
}