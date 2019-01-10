#include <algorithm>
#include <cstdio>

const int N = 250052, M = 19;
typedef long long ll;

struct edge { int to, next, w; } e[N*4];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}; head[x] = cnt;
}

int dfn[N], dep[N], par[N][M+1], mx[N][M+1], idx;
void dfs1(int x, int p, int d) {
	dfn[x] = ++idx; dep[x] = d; par[x][0] = p;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		mx[nx][0] = e[i].w;
		dfs1(nx, x, d+1);
	}
}

int n;
inline void init() {
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= n; j++) {
			par[j][i] = par[par[j][i-1]][i-1];
			mx[j][i] = std::min(mx[j][i-1], mx[par[j][i-1]][i-1]);
		}
	}
}
inline int lca(int x, int y, int& o) {
	o = 0x3f3f3f3f;
	if (dep[x] > dep[y]) std::swap(x, y);
	for (int i = M; ~i; i--) {
		if (dep[par[y][i]] >= dep[x]) {
			o = std::min(o, mx[y][i]);
			y = par[y][i];
		}
	}
	if (x == y) return x;
	for (int i = M; ~i; i--) {
		if (par[x][i] != par[y][i]) {
			o = std::min(o, std::min(mx[x][i], mx[y][i]));
			x = par[x][i]; y = par[y][i];
		}
	}
	return par[x][0];
}

int tag[N]; ll dp[N];
void dfs2(int x, int p) {
	dp[x] = 0;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		dfs2(nx, x);
		if (tag[nx]) dp[x] += e[i].w;
		else dp[x] += std::min(dp[nx], (ll)e[i].w);
	}
}

int m, k, x, y, z, t, a[N];
int st[N], top, _;
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z); addedge(y, x, z);
	}
	dfs1(1, 0, 1); init();
	for (scanf("%d", &m); m--; ) {
		scanf("%d", &k);
		for (int i = 1; i <= k; i++) {
			scanf("%d", a+i); tag[a[i]] = 1;
		}
		std::sort(a+1, a+k+1, [](int p, int q){
			return dfn[p] < dfn[q];
		});
		st[top = 1] = 1; cnt = head[1] = 0;
		for (int i = 1; i <= k; i++) {
			if (a[i] == 1) continue;
			int l = lca(st[top], a[i], t);
			if (l != st[top]) {
				while (dfn[l] < dfn[st[top-1]]) {
					lca(st[top-1], st[top], t);
					addedge(st[top-1], st[top], t);
					top--;
				}
				if (dfn[l] > dfn[st[top-1]]) {
					head[l] = 0;
					lca(l, st[top], t);
					addedge(l, st[top], t);
					st[top] = l;
				} else {
					lca(l, st[top], t);
					addedge(l, st[top--], t);
				}
			}
			head[a[i]] = 0;
			st[++top] = a[i];
		}
		for (int i = 1; i < top; i++) {
			lca(st[i], st[i+1], t);
			addedge(st[i], st[i+1], t);
		}
		dfs2(1, 0);
		printf("%lld\n", dp[1]);
		for (int i = 1; i <= k; i++) tag[a[i]] = 0;
	}
	return ~~(0^_^0);
}