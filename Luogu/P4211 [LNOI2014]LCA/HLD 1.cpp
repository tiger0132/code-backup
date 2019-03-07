#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using ll = long long;
const int N = 5e4 + 45, P = 201314;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}

namespace $ {
int n;
ll _[N], __[N];
void add(ll *a, int i, int x) {
	for (; i <= n; i += i & -i) a[i] += x;
}
ll query(ll *a, int i) {
	int ret = 0;
	for (; i; i -= i & -i) ret += a[i];
	return ret;
}
void add(int l, int r, int x) {
	add(_, l, x), add(_, r + 1, -x);
	add(__, l, x * (l - 1)), add(__, r + 1, -x * r);
}
ll query(int l, int r) { return query(_, r) * r - query(__, r) - query(_, l - 1) * (l - 1) + query(__, l - 1); }
}  // namespace $

int dfn[N], par[N], top[N], son[N], dep[N], sz[N], idx;
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
	dfn[x] = ++idx, top[x] = t;
	if (!son[x]) return;
	dfs2(son[x], t);
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == par[x] || nx == son[x]) continue;
		dfs2(nx, nx);
	}
}
void update(int x, int y, int z) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		$::add(dfn[top[x]], dfn[x], z);
		x = par[top[x]];
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	$::add(dfn[x], dfn[y], z);
}
int query(int x, int y) {
	ll sum = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		sum += $::query(dfn[top[x]], dfn[x]);
		x = par[top[x]];
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	sum += $::query(dfn[x], dfn[y]);
	return (sum % P + P) % P;
}

struct node {
	int x, opt, *ans;
};

int n, m, l, r, x, ans[N];
std::vector<node> v[N];

int main() {
	scanf("%d%d", &n, &m), $::n = n;
	for (int i = 2; i <= n; i++) {
		scanf("%d", &x);
		addedge(i, x + 1);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &l, &r, &x), l++, r++, x++;
		v[l - 1].push_back((node){x, -1, ans + i});
		v[r].push_back((node){x, 1, ans + i});
	}
	for (int i = 1; i <= n; i++) {
		update(1, i, 1);
		for (node j : v[i]) *j.ans = ((*j.ans + query(1, j.x) * j.opt) % P + P) % P;
	}
	for (int i = 1; i <= m; i++) {
		printf("%d\n", ans[i]);
	}
}