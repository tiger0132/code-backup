#include <algorithm>
#include <cstdio>
#include <cstring>
#define int unsigned

const int N = 1e5 + 51, M = 4e5 + 54, K = 19;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int dep[N], par[N], top[N], son[N], dfn[N], w[N], w_[N], sz[N], fa[N][K], idx;
void dfs1(int x, int p, int u) {
	x[fa][0] = x[par] = p, x[dep] = u, x[sz] = 1;
	for (int i = x[head], nx, mx = 0; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs1(nx, x, u + 1), x[sz] += nx[sz];
			if (mx < nx[sz]) mx = nx[sz], x[son] = nx;
		}
}
void dfs2(int x, int t) {
	x[dfn] = ++idx, x[top] = t, idx[w] = x[w_];
	if (x[son]) dfs2(x[son], t);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par] && nx != x[son]) dfs2(nx, nx);
}

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
int ch[M][2], mn[M], set[M], nc = 1;
void up(int x) { x[mn] = std::min(x[L][mn], x[R][mn]); }
void put(int x, int y) { x[mn] = x[set] = y; }
void pd(int x) { x[set] && (put(x[L], x[set]), put(x[R], x[set]), x[set] = 0); }
void build(int x, int l, int r, int *a) {
	if (l == r) return void(x[mn] = a[l]);
	build(x[L] = ++nc, l, mid, a), build(x[R] = ++nc, mid + 1, r, a), up(x);
}
void upd(int x, int l, int r, int ql, int qr, int y) {
	if (ql <= l && r <= qr) return put(x, y);
	pd(x);
	if (ql <= mid) upd(x[L], l, mid, ql, qr, y);
	if (mid < qr) upd(x[R], mid + 1, r, ql, qr, y);
	up(x);
}
int qry(int x, int l, int r, int ql, int qr) {
	if (ql > qr) return 3e9;
	if (ql <= l && r <= qr) return x[mn];
	pd(x);
	if (qr <= mid) return qry(x[L], l, mid, ql, qr);
	if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
	return std::min(qry(x[L], l, mid, ql, qr), qry(x[R], mid + 1, r, ql, qr));
}
int n, op, x, y, z, rt;
void upd(int x, int y, int z) {
	for (; x[top] != y[top]; upd(1, 1, n, x[top][dfn], x[dfn], z), x = x[top][par])
		if (x[top][dep] < y[top][dep]) std::swap(x, y);
	if (x[dep] > y[dep]) std::swap(x, y);
	upd(1, 1, n, x[dfn], y[dfn], z);
}
int kfa(int x, int k) {
	for (; k; k -= k & -k) x = x[fa][__builtin_ctz(k)];
	return x;
}
signed main() {
	scanf("%u%*u", &n), 0 [mn] = 3e9;
	for (int i = 1; i < n; i++) scanf("%u%u", &x, &y), addedge(x, y);
	for (int i = 1; i <= n; i++) scanf("%u", w_ + i);
	dfs1(1, 0, 1), dfs2(1, 1);
	build(1, 1, n, w);
	for (int i = 1; i < K; i++)
		for (int j = 1; j <= n; j++) j[fa][i] = j[fa][i - 1][fa][i - 1];
	scanf("%u", &rt);
	while (~scanf("%u%u", &op, &x)) {
		if (op == 1) rt = x;
		if (op == 2) {
			scanf("%u%u", &y, &z);
			upd(x, y, z);
		} else if (op == 3)
			if (x[dfn] < rt[dfn] && rt[dfn] < x[dfn] + x[sz]) {
				y = kfa(rt, rt[dep] - x[dep] - 1);
				printf("%u\n", std::min(qry(1, 1, n, 1, y[dfn] - 1),
										qry(1, 1, n, y[dfn] + y[sz], n)));
			} else if (x == rt)
				printf("%u\n", 1 [mn]);
			else
				printf("%u\n", qry(1, 1, n, x[dfn], x[dfn] + x[sz] - 1));
	}
}