#include <algorithm>
#include <cmath>
#include <cstdio>
#define col(x) (((x)-1) / m + 1)
#define lb(x) (((x)-1) * m + 1)
#define rb(x) std::min((x)*m, n)

using ll = long long;
const int N = 5e4 + 45, M = 3e2 + 23, P = 201314;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}

namespace $ {
int par[N], top[N], son[N], dep[N], m[N], idx;
void dfs1(int x, int p, int d) {
	sz[x] = 1, par[x] = p, dep[x] = d;
	int mx = -1;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		dfs1(nx, x, d + 1);
		sz[x] += sz[nx];
		if (sz[nx] > mx) {
			son[x] = nx;
			mx = sz[nx];
		}
	}
}
void dfs2(int x, int t) {
	top[x] = t;
	if (!son[x]) return;
	dfs2(son[x], t);
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == par[x] || nx == son[x]) continue;
		dfs2(nx, nx);
	}
}
int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		x = par[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}
};					   // namespace $
using $::lca, $::dep;  // C++17!

ll sz[N], _[N];
void dfs1(int x, int p, int l, int r) {
	sz[x] = l <= x && x <= r;
	for (int i = head[x], nx; i; i = e[i].next) {
		if ((nx = e[i].to) == p) continue;
		dfs1(nx, x, l, r);
		sz[x] += sz[nx];
		_[x] += _[nx] + sz[nx];
	}
}

ll sdis[M][N];
void dfs2(int x, int p, int id) {
	sdis[id][x] = _[x];
	for (int i = head[x], nx; i; i = e[i].next) {
		if ((nx = e[i].to) == p) continue;
		ll u = _[x] - sz[nx] - _[nx], v = sz[x] - sz[nx];
		_[nx] += u + v;
		sz[nx] = sz[x];
		dfs2(nx, x, id);
	}
	printf("%d %d: %lld\n", id, x, sdis[id][x]);
}

int n, m, q, l, r, x, sdep[N];
int main() {
	scanf("%d%d", &n, &q), m = 300;
	for (int i = 2; i <= n; i++) {
		scanf("%d", &x);
		addedge(i, x + 1);
	}
	$::dfs1(1, 0, 1), $::dfs2(1, 1);
	printf("%d\n", lca(4, 5));
	for (int i = 1; i <= n; i++) sdep[i] = sdep[i - 1] + dep[i];
	for (int i = 1; i <= 1; i++) {
		dfs1(1, 0, lb(i), rb(i));
		dfs2(1, 0, i);
	}
	while (q--) {
		scanf("%d%d%d", &l, &r, &x);
		l++, r++, x++;
		int L = col(l), R = col(R);
		ll ans = 0, tmp = 0;
		for (int i = l; i <= std::min(rb(L), r); i++) ans += dep[lca(i, x)];
		printf("[%d, %d]\n", l, std::min(rb(L), r));
		printf("# %lld\n", ans);
		if (L != R)
			for (int i = lb(R); i <= r; i++) ans += dep[lca(i, x)];
		printf("[%d, %d]\n", lb(R), r);
		printf("# %lld\n", ans);
		l = std::min(rb(L), r), r = lb(R);
		tmp = sdep[r] - sdep[l - 1] + (r - l + 1ll) * dep[x];
		for (int i = L + 1; i < R; i++) tmp -= sdis[i][x];
		printf("[%d, %d]\n", lb(L + 1), rb(R - 1));
		printf("# %lld %lld\n", ans, tmp);
		ans += tmp / 2;
		printf("%lld\n", ans % P);
	}
}