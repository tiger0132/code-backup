#include <algorithm>
#include <cstring>
#include <cstdio>

typedef long long ll;
const int N = 2e4+42, M = 15, K = 60;

struct $ {
	ll lb[K+1];
	inline $(const $& rhs) { memcpy(lb, rhs.lb, sizeof lb); }
	inline $() { memset(lb, 0, sizeof lb); }
	inline void insert(ll x) {
		for (ll i = K; i >= 0; i--) if ((x >> i) & 1) {
			if (!lb[i]) return (void)(lb[i] = x);
			x ^= lb[i];
		}
	}
	inline void merge(const $& rhs) {
		for (int i = 0; i <= K; i++) if (rhs.lb[i]) insert(rhs.lb[i]);
	}
	inline ll ans() {
		ll ret = 0;
		for (int i = K; i >= 0; i--) ret = std::max(ret, ret ^ lb[i]);
		return ret;
	}
};

struct edge { int to, next; } e[N<<1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}; head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}; head[y] = cnt;
}

int dfn[N], dep[N], par[N][M+1], idx;
$ mx[N][M+1]; ll w[N];
int n;
void dfs1(int x, int p, int d) {
	dfn[x] = ++idx; dep[x] = d; par[x][0] = p;
	mx[x][0].insert(w[x]);
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		dfs1(nx, x, d+1);
	}
}
inline void init() {
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= n; j++) {
			par[j][i] = par[par[j][i-1]][i-1];
			mx[j][i] = mx[j][i-1];
			mx[j][i].merge(mx[par[j][i-1]][i-1]);
		}
	}
}
inline ll query(int x, int y) {
	$ ret;
	if (dep[x] > dep[y]) std::swap(x, y);
	for (int i = M; ~i; i--) {
		if (dep[par[y][i]] >= dep[x]) {
			ret.merge(mx[y][i]);
			y = par[y][i];
		}
	}
	if (x == y) {
		ret.insert(w[x]);
		return ret.ans();
	}
	for (int i = M; ~i; i--) {
		if (par[x][i] != par[y][i]) {
			ret.merge(mx[x][i]); ret.merge(mx[y][i]);
			x = par[x][i]; y = par[y][i];
		}
	}
	ret.insert(w[x]); ret.insert(w[y]);
	ret.insert(w[par[x][0]]);
	return ret.ans();
}

int m, x, y;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", w+i);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	dfs1(1, 0, 1);
	init();
	while (m--) {
		scanf("%d%d", &x, &y);
		printf("%lld\n", query(x, y));
	}
}