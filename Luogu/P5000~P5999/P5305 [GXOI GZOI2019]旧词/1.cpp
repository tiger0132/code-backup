#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define int long long

const int N = 4e5 + 54, P = 998244353;
struct node {
	int x, *ans;
};

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * x * r % P;
	return r;
}
void ad(int &x, int y) {
	if ((x += y) >= P) x -= P;
}
int add(int x, int y) { return (x += y) >= P ? x - P : x; }
int swgt[N];

// SGT begin
#define L ch][0
#define R ch][1
int ch[N][2], l[N], r[N], mid[N], w[N], s[N], t[N], nc = 1;
void put(int x, int v = 1) { ad(x[s], 1ll * v * x[w] % P), x[t] += v; }
void up(int x) { x[s] = add(x[L][s], x[R][s]); }
void pd(int x) { put(x[L], x[t]), put(x[R], x[t]), x[t] = 0; }
void build(int x, int ql, int qr, int *a) {
	x[mid] = (ql + qr) / 2, x[l] = ql, x[r] = qr;
	if (ql == qr) return void(x[w] = a[ql]);
	build(x[L] = ++nc, ql, x[mid], a), build(x[R] = ++nc, x[mid] + 1, qr, a);
	x[w] = x[L][w] + x[R][w], up(x);
}
void upd(int x, int ql, int qr) {
	pd(x);
	if (ql <= x[l] && x[r] <= qr) return put(x);
	if (ql <= x[mid]) upd(x[L], ql, qr);
	if (x[mid] < qr) upd(x[R], ql, qr);
	up(x);
}
int qry(int x, int ql, int qr) {
	pd(x);
	if (ql <= x[l] && x[r] <= qr) return x[s];
	int r = 0;
	if (ql <= x[mid]) ad(r, qry(x[L], ql, qr));
	if (x[mid] < qr) ad(r, qry(x[R], ql, qr));
	return r;
}
// SGT end

// HLD begin
int k, par[N], dfn[N], top[N], son[N], sz[N], dep[N], wgt[N], idx;
void dfs1(int x, int d) {
	x[dep] = d;
	for (int i = x[head], nx, mx = 0; i; i = e[i].next) {
		dfs1(nx = e[i].to, d + 1), nx[par] = x, x[sz] += nx[sz];
		if (nx[sz] >= mx) mx = nx[sz], x[son] = nx;
	}
}
void dfs2(int x, int t) {
	x[dfn] = ++idx, x[top] = t, idx[wgt] = add(pw(x[dep], k) - pw(x[dep] - 1, k), P);
	if (!x[son]) return;
	dfs2(x[son], t);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[son]) dfs2(nx, nx);
}
void upd(int x) {
	for (; x[top] != 1; x = x[top][par]) upd(1, x[top][dfn], x[dfn]);
	upd(1, 1, x[dfn]);
}
int qry(int x) {
	int r = 0;
	for (; x[top] != 1; x = x[top][par]) ad(r, qry(1, x[top][dfn], x[dfn]));
	return add(r, qry(1, 1, x[dfn]));
}
// HLD end

std::vector<node> queries[N];
int n, q, x, y, ans[N];
signed main() {
	scanf("%lld%lld%lld", &n, &q, &k);
	for (int i = 2; i <= n; i++) scanf("%lld", &x), addedge(x, i);
	dfs1(1, 1), dfs2(1, 1), build(1, 1, n, wgt);
	for (int i = 1; i <= n; i++) swgt[i] = add(wgt[i], swgt[i - 1]);
	for (int i = 1; i <= q; i++) {
		scanf("%lld%lld", &x, &y);
		x[queries].push_back({y, ans + i});
	}
	for (int i = 1; i <= n; i++) {
		upd(i);
		for (auto j : i[queries]) *j.ans = qry(j.x);
	}
	for (int i = 1; i <= q; i++) printf("%lld\n", ans[i]);
}