#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 4e4 + 44;
const ll K = 3e9;
struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int w) {
	e[++cnt] = (edge){y, x[head], w}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head], w}, y[head] = cnt;
}

struct SGT {
#define L ch][0
#define R ch][1
#define mid (l + r) / 2
	static const int M = N << 5;
	int ch[M][2], nc;
	ll s[M], s2[M];
	void upd(int &x, ll l, ll r, int i, int y) {
		if (!x) x = ++nc;
		if (x[s] += y, x[s2] += i * y, l == r) return;
		i <= mid ? upd(x[L], l, mid, i, y) : upd(x[R], mid + 1, r, i, y);
	}
	ll qry(int x, ll l, ll r, int ql, int qr, ll *a) {
		if (!x) return 0;
		if (ql <= l && r <= qr) return x[a];
		if (qr <= mid) return qry(x[L], l, mid, ql, qr, a);
		if (mid < ql) return qry(x[R], mid + 1, r, ql, qr, a);
		return qry(x[L], l, mid, ql, qr, a) + qry(x[R], mid + 1, r, ql, qr, a);
	}
	void clear() {
		memset(ch + 1, 0, nc << 3);
		memset(s + 1, 0, nc << 2);
		memset(s2 + 1, 0, nc << 2);
		nc = 0;
	}
} sgt;

int dep[N], par[N], sz[N], son[N], rt, qry_k;
ll ans1, ans2;
void dfs1(int x, int p, int d) {
	x[par] = p, x[sz] = 1, x[dep] = d;
	for (int i = x[head], nx, mx = 0; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs1(nx, x, d + e[i].w), x[sz] += nx[sz];
			if (nx[sz] > mx) mx = nx[sz], x[son] = nx;
		}
}
void add(int x) {
	// printf("add %d, %d\n", x, x[dep]);
	sgt.upd(rt, 0, K, x[dep], 1);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par]) add(nx);
}
void del(int x) {
	// printf("del %d, %d\n", x, x[dep]);
	sgt.upd(rt, 0, K, x[dep], -1);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par]) del(nx);
}
void calc(int x, int t) {
	int l = qry_k - x[dep] + 2 * t[dep];
	if (l >= 0) {
		ans1 += sgt.qry(rt, 0, K, 0, l, sgt.s);
		ans2 += sgt.qry(rt, 0, K, 0, l, sgt.s2);
	}
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par]) calc(nx, t);
}
void dfs3(int x, bool f) {
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par] && nx != x[son]) dfs3(nx, false);
	if (x[son]) dfs3(x[son], true);
	int l = qry_k + x[dep];
	if (l >= 0) {
		// printf("qry %d, [%d, %d]\n", x, 0, l);
		ans1 += sgt.qry(rt, 0, K, 0, l, sgt.s);
		ans2 += sgt.qry(rt, 0, K, 0, l, sgt.s2);
	}
	sgt.upd(rt, 0, K, x[dep], 1);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par] && nx != x[son]) calc(nx, x), add(nx);
	if (!f) del(x);
}
void exec(int k) {
	qry_k = k;
	sgt.clear(), rt = 0;
	dfs3(1, true);
}

int n, m, x, y, z;
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) scanf("%d%d%d", &x, &y, &z), addedge(x, y, z);
	dfs1(1, 1, 0);
	scanf("%d", &m);
	exec(m);
	printf("%lld\n", ans1);
	// printf("%d %d\n", ans1, ans2);
}