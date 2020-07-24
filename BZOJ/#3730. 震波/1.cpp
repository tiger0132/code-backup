#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define mid (l + r) / 2
#define L ch][0
#define R ch][1

typedef std::pair<int, int> pii;
const int N = 4e5 + 54, M = 1e7 + 71, LN = 20, INF = 1e9;

std::vector<int> g[N];
int v[N], c[N];

struct {
	int occ[N << 1], dep[N], idx;
	pii st[N << 1][LN];
	void dfs2(int x, int p = 0, int d = 0) {
		st[x[occ] = ++idx][0] = {d, x}, x[dep] = d;
		for (int nx : x[g])
			if (nx != p) dfs2(nx, x, d + 1), st[++idx][0] = {d, x};
	}
	void init() {
		dfs2(1);
		for (int j = 1; (1 << j) <= idx; j++)
			for (int i = 1; i + (1 << j) - 1 <= idx; i++)
				st[i][j] = std::min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	}
	int lca(int x, int y) {
		int l = x[occ], r = y[occ];
		if (l > r) std::swap(l, r);
		int k = 31 - __builtin_clz(r - l + 1);
		return std::min(st[l][k], st[r - (1 << k) + 1][k]).second;
	}
	inline int operator()(int x, int y) { return x[dep] + y[dep] - 2 * lca(x, y)[dep]; }
} dist;

int ch[M][2], s[M], nc = 1;
struct SGT {
	int rt;
	void upd(int& x, int l, int r, int i, int y) {
		if (!x) x = ++nc;
		if (x[s] += y, l == r) return;
		if (i <= mid) return upd(x[L], l, mid, i, y);
		upd(x[R], mid + 1, r, i, y);
	}
	int qry(int x, int l, int r, int ql, int qr) {
		if (!x) return 0;
		if (ql <= l && r <= qr) return x[s];
		if (qr <= mid) return qry(x[L], l, mid, ql, qr);
		if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
		return qry(x[L], l, mid, ql, qr) + qry(x[R], mid + 1, r, ql, qr);
	}
} S1[N], S2[N];

int rt, sz[N], dsiz[N], mx[N], p[N];
bool vis[N];
void dfs2(int x, int p, int sum) {
	x[sz] = 1, x[mx] = 0;
	for (int nx : x[g])
		if (!nx[vis] && nx != p) {
			dfs2(nx, x, sum), x[sz] += nx[sz];
			x[mx] = std::max(x[mx], nx[sz]);
		}
	x[mx] = std::max(x[mx], sum - x[sz]);
	if (!rt || x[mx] < rt[mx]) rt = x;
}
void divi(int x, int sum) {
	x[vis] = true;
	dsiz[x] = sum;
	for (int nx : x[g])
		if (!nx[vis]) {
			int ns = nx[sz] < x[sz] ? nx[sz] : sum - x[sz];
			rt = 0, dfs2(nx, x, ns);
			rt[p] = x, divi(rt, ns);
		}
}

int n;
void upd(int x, int y) {
	for (int cur = x, f; f = cur[p], cur; cur = f) {
		cur[S1].upd(cur[S1].rt, 0, n, dist(cur, x), y);
		if (f) cur[S2].upd(cur[S2].rt, 0, n, dist(f, x), y);
	}
}
int qry(int x, int k) {
	int ret = 0;
	for (int cur = x, last = 0; cur; last = cur, cur = cur[p]) {
		int d = dist(x, cur);
		if (d > k) continue;
		ret += cur[S1].qry(cur[S1].rt, 0, n, 0, k - d);
		if (last) ret -= last[S2].qry(last[S2].rt, 0, n, 0, k - d);
	}
	return ret;
}

int m, op, x, y, la;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", v + i);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		x[g].push_back(y);
		y[g].push_back(x);
	}
	dist.init();
	dfs2(1, 0, n);
	divi(rt, n);

	for (int i = 1; i <= n; i++) upd(i, i[v]);
	while (m--) {
		scanf("%d%d%d", &op, &x, &y), x ^= la, y ^= la;
		if (op == 0)
			printf("%d\n", la = qry(x, y));
		else
			upd(x, y - x[v]), x[v] = y;
	}
}