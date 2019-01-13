#include <algorithm>
#include <cstdio>

const int N = 1e6+61, M = 20, INF = 0x3f3f3f3f, MINF = 0xc0c0c0c0;
typedef long long ll;

struct edge { int to, next; } e[N*4];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}; head[x] = cnt;
}

int dfn[N], dep[N], par[N][M+1], idx;
void dfs1(int x, int p, int d) {
	dfn[x] = ++idx; dep[x] = d; par[x][0] = p;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		dfs1(nx, x, d+1);
	}
}

int n;
inline void init() {
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= n; j++) {
			par[j][i] = par[par[j][i-1]][i-1];
		}
	}
}
inline int lca(int x, int y) {
	if (dep[x] > dep[y]) std::swap(x, y);
	for (int i = M; ~i; i--) {
		if (dep[par[y][i]] >= dep[x]) {
			y = par[y][i];
		}
	}
	if (x == y) return x;
	for (int i = M; ~i; i--) {
		if (par[x][i] != par[y][i]) {
			x = par[x][i]; y = par[y][i];
		}
	}
	return par[x][0];
}

int k, sz[N], mi[N], mx[N];
ll tot; int mi$, mx$;
int tag[N];
void dfs2(int x) {
	if (tag[x]) mi[x] = mx[x] = 0;
	else mi[x] = INF, mx[x] = MINF;
	sz[x] = tag[x];
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to, w = dep[nx] - dep[x];
		dfs2(nx);
		tot += (ll)sz[nx] * (k - sz[nx]) * w;
		mi$ = std::min(mi$, mi[x] + mi[nx] + w);
		mx$ = std::max(mx$, mx[x] + mx[nx] + w);
		mi[x] = std::min(mi[x], mi[nx] + w);
		mx[x] = std::max(mx[x], mx[nx] + w);
		sz[x] += sz[nx];
	}
	// printf("[%d(%d): %d, %d, %d]\n", x, tag[x], sz[x], mi[x], mx[x]);
}

int m, x, y, a[N];
int st[N], top, _;
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		addedge(x, y); addedge(y, x);
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
			int l = lca(st[top], a[i]);
			if (l != st[top]) {
				while (dfn[l] < dfn[st[top-1]]) {
					addedge(st[top-1], st[top]);
					top--;
				}
				if (dfn[l] > dfn[st[top-1]]) {
					head[l] = 0;
					addedge(l, st[top]);
					st[top] = l;
				} else {
					addedge(l, st[top--]);
				}
			}
			head[a[i]] = 0;
			st[++top] = a[i];
		}
		for (int i = 1; i < top; i++) {
			addedge(st[i], st[i+1]);
		}
		tot = 0; mi$ = INF; mx$ = MINF;
		dfs2(1);
		printf("%lld %d %d\n", tot, mi$, mx$);
		for (int i = 1; i <= k; i++) tag[a[i]] = 0;
	}
	return ~~(0^_^0);
}