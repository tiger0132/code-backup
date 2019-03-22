#include <algorithm>
#include <cassert>
#include <cstring>
#include <cstdio>

const int N = 2e5+52, M = 1e6+61, INF = 0x01010101;

struct edge { int to, next, w; } e[N<<1];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}; head[x] = cnt;
	e[++cnt] = (edge){x, head[y], z}; head[y] = cnt;
}

int n, k, ans;

int sz[N], mst[N], vis[N], ncnt, rt;
void dfs1(int x, int p, int d=1) {
	sz[x] = 1; mst[x] = 0;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p || vis[nx]) continue;
		dfs1(nx, x, d+1);
		sz[x] += sz[nx];
		mst[x] = std::max(mst[x], sz[nx]);
	}
	mst[x] = std::max(mst[x], ncnt - sz[x]);
	if (mst[x] < mst[rt]) rt = x;
}
int cnt_[M], dep[N], dis[N], stx[N], topx, idx;
void dfs2(int x, int p, int d, int _x) {
	if (_x > k) return;
	cnt_[_x] = std::min(cnt_[_x], d);
	stx[++topx] = _x;
	dis[++idx] = _x;
	dep[idx] = d;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p || vis[nx]) continue;
		dfs2(nx, x, d+1, _x + e[i].w);
	}
}
int _[M], st[N], top;
void calc(int x) {
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (vis[nx]) continue;
		idx = 0;
		while (topx) cnt_[stx[topx--]] = 0x01010101;
		dfs2(nx, x, 1, e[i].w);
		for (int j = 1; j <= idx; j++) {
			if (k >= dis[j]) ans = std::min(ans, _[k - dis[j]] + dep[j]);
		}
		for (int j = 1; j <= idx; j++) {
			st[++top] = dis[j];
			_[dis[j]] = std::min(_[dis[j]], cnt_[dis[j]]);
		}
	}
	while (top) _[st[top--]] = 0x01010101;
}
void solve(int x) {
	vis[x] = 1; _[0] = 0;
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

signed main() {
	ans = INF;
	scanf("%d%d", &n, &k);
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &x, &y, &z); x++; y++;
		addedge(x, y, z);
	}
	ncnt = n; mst[rt] = INF;
	memset(cnt_, 0x01, sizeof cnt_);
	memset(_, 0x01, sizeof _);
	dfs1(1, 0);
	solve(rt);
	printf("%d", ans == INF ? -1 : ans);
}