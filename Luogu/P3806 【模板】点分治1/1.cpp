#include <algorithm>
#include <cstdio>

const int N = 1e5+15, INF = 0x3f3f3f3f;

struct edge { int to, next, w; } e[N<<1];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}; head[x] = cnt;
	e[++cnt] = (edge){x, head[y], z}; head[y] = cnt;
}

int n, m, q[N], ans[N];

int sz[N], mst[N], vis[N], ncnt, rt;
void dfs1(int x, int p) {
	sz[x] = 1; mst[x] = 0;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p || vis[nx]) continue;
		dfs1(nx, x);
		sz[x] += sz[nx];
		mst[x] = std::max(mst[x], sz[nx]);
	}
	mst[x] = std::max(mst[x], ncnt - sz[x]);
	if (mst[x] < mst[rt]) rt = x;
}
int dis[N], dis$[N], idx;
void dfs2(int x, int p) {
	dis$[++idx] = dis[x];
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p || vis[nx]) continue;
		dis[nx] = dis[x] + e[i].w;
		dfs2(nx, x);
	}
}
int _[N], st[N], top;
void calc(int x) {
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (vis[nx]) continue;
		// printf("(%d) -- (%d): %d\n", x, nx, e[i].w);
		idx = 0; dis[nx] = e[i].w;
		dfs2(nx, x);
		for (int j = 1; j <= idx; j++) {
			for (int k = 1; k <= m; k++) {
				// printf("%d - %d\n", q[k], dis$[j]);
				if (q[k] >= dis$[j]) ans[k] |= _[q[k] - dis$[j]];
			}
		}
		for (int j = 1; j <= idx; j++) {
			st[++top] = dis$[j];
			_[dis$[j]] = 1;
		}
	}
	while (top) _[st[top--]] = 0;
}
void solve(int x) {
	// printf("solve %d\n", x);
	vis[x] = _[0] = 1;
	calc(x);
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (vis[nx]) continue;
		ncnt = sz[nx]; mst[rt = 0] = INF;
		dfs1(nx, 0);
		solve(rt);
	}
}

int x, y, z;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", q+i);
	}
	ncnt = n; mst[rt] = INF;
	dfs1(1, 0);
	solve(rt);
	for (int i = 1; i <= m; i++) {
		puts(ans[i] ? "AYE" : "NAY");
	}
}