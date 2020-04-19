#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <utility>
#include <vector>
#define int long long

typedef std::pair<int, int> pii;
const int N = 1e5 + 51;

struct pSGT {
#define L ch][0
#define R ch][1
#define mid (l + r) / 2
	static const int M = N << 6;
	int w[M], t[M], s[M], *prew;
	int ch[M][2], nc;
	inline int cl(int x) {
		return nc++, nc[L] = x[L], nc[R] = x[R], nc[t] = x[t], nc[s] = x[s], nc[w] = x[w],
					 nc;
	}
	void build(int& x, int l, int r, int* a) {
		if (x = ++nc, l == r) return x[w] = a[l], void();
		build(x[L], l, mid, a), build(x[R], mid + 1, r, a), x[w] = x[L][w] + x[R][w];
	}
	int qry(int x, int l, int r, int ql, int qr) {
		int v = (prew[qr] - prew[ql - 1]) * x[t];
		if (ql == l && r == qr) return x[s] + v;
		if (qr <= mid) return v + qry(x[L], l, mid, ql, qr);
		if (mid < ql) return v + qry(x[R], mid + 1, r, ql, qr);
		return v + qry(x[L], l, mid, ql, mid) + qry(x[R], mid + 1, r, mid + 1, qr);
	}
	void upd(int& x, int l, int r, int ql, int qr, int y) {
		if (x = cl(x), ql == l && r == qr) return x[t] += y, void();
		x[s] += prew[qr] - prew[ql - 1];
		if (qr <= mid) return upd(x[L], l, mid, ql, qr, y);
		if (mid < ql) return upd(x[R], mid + 1, r, ql, qr, y);
		upd(x[L], l, mid, ql, mid, y), upd(x[R], mid + 1, r, mid + 1, qr, y);
	}
};
struct HLD {
	int n, dfn[N], sz[N], par[N], dep[N], top[N], son[N], w[N], rt[N], pre[N], prew[N],
		dis[N];
	std::vector<pii> g[N];
	pSGT sgt;
	void operator()(int x, int y, int z) {
		x[g].push_back({y, z});
		y[g].push_back({x, z});
	}
	void upd(int x, int& _rt) {
		for (; x; x = x[top][par]) sgt.upd(_rt, 1, n, x[top][dfn], x[dfn], 1);
	}
	int qry(int x, int _rt) {
		int ret = 0;
		for (; x; x = x[top][par])
			//  ret += sgt.qry(_rt, 1, n, x[top][dfn], x[dfn]);
			ret += sgt.qry(_rt, 1, n, x[top][dfn], x[dfn]),
				printf("(%lld, %lld)", x[top][dfn], x[dfn]);
		return ret;
	}
	void build(int nn, int root, int* id, int* ord) {
		int idx = 0;
		n = nn;
		std::function<void(int, int)> dfs1 = [&](int x, int _d) {
			x[sz] = 1, id[x][pre] = _d, x[dis] = _d;
			for (auto [nx, nw] : x[g])
				if (nx != x[par]) {
					nx[dep] = x[dep] + 1, nx[par] = x, dfs1(nx, _d + nw), x[sz] += nx[sz];
					if (nx[sz] >= x[son][sz]) x[son] = nx;
				}
		};
		std::function<void(int, int, int)> dfs2 = [&](int x, int t, int _w) {
			x[top] = t, x[dfn] = ++idx, idx[w] = _w;
			for (auto [nx, nw] : x[g])
				if (nx != x[par]) dfs2(nx, nx == x[son] ? t : nx, nw);
		};
		dfs1(root, 0), dfs2(root, root, 0);
		for (int i = 1; i <= n; i++) prew[i] = prew[i - 1] + w[i];
		for (int i = 1; i <= n; i++) pre[i] += pre[i - 1];
		sgt.prew = prew, sgt.build(rt[0], 1, n, w);
		// for (int i = 1; i <= n; i++) printf("%lld%c", id[i], " \n"[i == n]);
		for (int i = 1; i <= n; i++) upd(ord[i], rt[i] = rt[i - 1]);
	}
	int qry(int x, int l, int r) {
		// printf("[%lld %lld %lld]", x, l, r);
		// printf("[%lld %lld %lld]", (r - l + 1) * dis[x], pre[r] - pre[l - 1],
		//    2 * (qry(x, rt[r]) - qry(x, rt[l - 1])));
		return (r - l + 1) * dis[x] + pre[r] - pre[l - 1] -
			   2 * (qry(x, rt[r]) - qry(x, rt[l - 1]));
	}
} hld;
struct D {
	pii v[N];
	int cnt;
	void operator+=(pii x) { v[++cnt] = x; }
	void build() { std::sort(v + 1, v + cnt + 1); }
	int operator()(pii x) { return std::lower_bound(v + 1, v + cnt + 1, x) - v; }
	int upbd(pii x) { return std::upper_bound(v + 1, v + cnt + 1, x) - v - 1; }
} mp;

int n, m, k, x, y, z, l, r, la, a[N], id[N], ord[N];
char op[2];
signed main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i), mp += {a[i], i};
	mp.build();
	for (int i = 1; i <= n; i++) id[mp.v[i].second] = i;
	for (int i = 1; i <= n; i++) ord[i] = mp.v[i].second;
	for (int i = 1; i < n; i++) scanf("%lld%lld%lld", &x, &y, &z), hld(x, y, z);
	hld.build(n, 1, id, ord);
	while (m--) {
		scanf("%lld%lld%lld", &x, &y, &z);
		l = (y + la) % k, r = (z + la) % k;
		if (l > r) std::swap(l, r);
		printf("%lld\n", la = hld.qry(x, mp({l, 0}), mp.upbd({r, 1e9})));
	}
}