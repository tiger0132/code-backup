#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 8e5 + 58;

#define L ch][0
#define R ch][1
struct tag {
	int s, la, ra, gss;
	void operator=(int x) { s = x, la = ra = gss = std::max(x, 0); }
	tag operator+(const tag& r) const {
		return {s + r.s, std::max(la, s + r.la), std::max(ra + r.s, r.ra),
				std::max({gss, r.gss, ra + r.la})};
	}
} t[N];
int ch[N][2], l[N], r[N], mid[N], set[N], nc = 1;
void up(int x) { x[t] = x[L][t] + x[R][t]; }
void put(int x, int v) { x[set] = v, x[t] = (x[r] - x[l] + 1) * v; }
void pd(int x) {
	if (x[set] != 1e7) put(x[L], x[set]), put(x[R], x[set]), x[set] = 1e7;
}
void upd(int x, int ql, int qr, int v) {
	if (ql <= x[l] && x[r] <= qr) return put(x, v);
	pd(x);
	if (ql <= x[mid]) upd(x[L], ql, qr, v);
	if (x[mid] < qr) upd(x[R], ql, qr, v);
	up(x);
}
tag qry(int x, int ql, int qr) {
	if (ql <= x[l] && x[r] <= qr) return x[t];
	pd(x);
	if (qr <= x[mid]) return qry(x[L], ql, qr);
	if (x[mid] < ql) return qry(x[R], ql, qr);
	return qry(x[L], ql, qr) + qry(x[R], ql, qr);
}
void build(int x, int ql, int qr, int* a) {
	x[l] = ql, x[r] = qr, x[mid] = (ql + qr) / 2, x[set] = 1e7;
	if (ql == qr) return void(x[t] = a[ql]);
	build(x[L] = ++nc, ql, x[mid], a), build(x[R] = ++nc, x[mid] + 1, qr, a), up(x);
}

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = {y, x[head]}, x[head] = cnt;
	e[++cnt] = {x, y[head]}, y[head] = cnt;
}

int par[N], dep[N], dfn[N], top[N], son[N], sz[N], w[N], nw[N], idx;
void dfs1(int x, int p, int d) {
	x[par] = p, x[dep] = d, x[sz] = 1;
	for (int i = x[head], nx, mx = 0; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs1(nx, x, d + 1), x[sz] += nx[sz];
			if (nx[sz] > mx) mx = nx[sz], x[son] = nx;
		}
}
void dfs2(int x, int t) {
	x[dfn] = ++idx, x[top] = t, idx[nw] = x[w];
	if (!x[son]) return;
	dfs2(x[son], t);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par] && nx != x[son]) dfs2(nx, nx);
}
void upd(int x, int y, int v) {
	for (; x[top] != y[top]; x = x[top][par]) {
		if (x[top][dep] < y[top][dep]) std::swap(x, y);
		upd(1, x[top][dfn], x[dfn], v);
	}
	if (x[dep] > y[dep]) std::swap(x, y);
	upd(1, x[dfn], y[dfn], v);
}
int qry(int x, int y) {
	tag l{}, r{};
	for (int tx, ty; (tx = x[top]) != (ty = y[top]);)
		if (tx[dep] > ty[dep])
			l = qry(1, tx[dfn], x[dfn]) + l, x = tx[par];
		else
			r = r + qry(1, ty[dfn], y[dfn]), y = ty[par];
	if (x[dep] > y[dep])
		l = qry(1, y[dfn], x[dfn]) + l;
	else
		r = r + qry(1, x[dfn], y[dfn]);
	std::swap(l.la, l.ra);
	return (l + r).gss;
}

int n, m, op, x, y, z;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", w + i);
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	dfs1(1, 0, 1), dfs2(1, 1), build(1, 1, n, nw);
	for (scanf("%d", &m); m--;) {
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1)
			printf("%d\n", qry(x, y));
		else
			scanf("%d", &z), upd(x, y, z);
	}
}