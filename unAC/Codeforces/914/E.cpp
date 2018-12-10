#include <algorithm>
#include <cassert>
#include <cstring>
#include <cstdio>

const int N = 2e5+52, M = 2e7+72, INF = 0x01010101;

struct edge { int to, next; } e[N<<1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}; head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}; head[y] = cnt;
}

int n, ans[N];
char rec[N];

inline int chk(int x) { return !(x & (x-1)); }

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
int cnt_[M], hv[N], stx[N], idx, topx;
void dfs2(int x, int p, int hash) {
	printf("    %d: (%d)\n", x, hash);
	hv[++idx] = hash;
	stx[++topx] = hash;
	cnt_[hash]++;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p || vis[nx]) continue;
		dfs2(nx, x, hash ^ (1 << rec[nx]));
	}
}
int _[M], _t[M], st[N], top;
void calc(int x) {
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (vis[nx]) continue;
		idx = 0;
		while (topx) cnt_[stx[topx--]] = 0;
		printf("[%d] -- [%d]:\n", x, nx);
		dfs2(nx, x, (1 << rec[x]) ^ (1 << rec[nx]));
		for (int j = 1; j <= idx; j++) {
			ans[x] += cnt_[hv[j]] * _[hv[j]];
			if (cnt_[hv[j]] && _[hv[j]]) printf("    (%d * %d)\n", hv[j], hv[j]);
			for (int k = 1; k <= (1 << 19); k <<= 1) {
				ans[x] += cnt_[hv[j]] * _[k ^ hv[j]];
				if (cnt_[hv[j]] && _[k ^ hv[j]]) printf("    (%d * %d)\n", hv[j], k ^ hv[j]);
			}
		}
		for (int j = 1; j <= idx; j++) {
			st[++top] = (1 << rec[x]) ^ hv[j];
			_[(1 << rec[x]) ^ hv[j]] += cnt_[hv[j]];
		}
	}
	for (int i = 1; i <= top; i++) {
		_t[st[top] ^ (1 << rec[i])] = _[st[top]];
		_[st[top]] = 0;
	}
	for (int i = 1; i <= top; i++) {
		_[st[top] ^ (1 << rec[i])] = _t[st[top] ^ (1 << rec[i])];
	}
	while (top) _[st[top--]] = 0;
}
void solve(int x) {
	printf("solve %d\n", x);
	vis[x] = 1; _[0] = 1;
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
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	scanf("%s", rec+1);
	for (int i = 1; i <= n; i++) rec[i] -= 'a';
	ncnt = n; mst[rt] = INF;
	dfs1(1, 0);
	solve(rt);
	for (int i = 1; i <= n; i++) {
		printf("%d ", ans[i]+1);
	}
}

#if 0
a	1
b	2
c	4
#endif