#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>

const int N = 2e3 + 32, M = 2e6 + 62, INF = 0x3f3f3f3f, K = 9;

struct edge {
	int to, next, w;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], z}, head[y] = cnt;
}
int lv[N];
bool bfs(int s, int t) {
	memset(lv, 0, sizeof lv);
	std::queue<int> q;
	lv[s] = 1;
	for (q.push(s); !q.empty(); q.pop()) {
		int x = q.front();
		for (int i = head[x]; i; i = e[i].next) {
			int nx = e[i].to;
			if (!e[i].w || lv[nx]) continue;
			lv[nx] = lv[x] + 1;
			q.push(nx);
		}
	}
	return lv[t];
}
int dfs(int s, int t, int f) {
	if (s == t || !f) return f;
	int r = 0;
	for (int i = head[s]; f && i; i = e[i].next) {
		int nx = e[i].to;
		if (!e[i].w || lv[nx] != lv[s] + 1) continue;
		int tmp = dfs(nx, t, std::min(f, e[i].w));
		e[i].w -= tmp, e[i ^ 1].w += tmp;
		f -= tmp, r += tmp;
	}
	if (f) lv[s] = -1;
	return r;
}
inline void clear() {
	for (int i = 2; i < cnt; i += 2) e[i].w = e[i ^ 1].w = (e[i].w + e[i ^ 1].w) / 2;
}
inline int dinic(int s, int t) {
	int ret = 0;
	clear();
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}

edge e2[N << 1];
int head2[N], cnt2 = 1;
void addedge2(int x, int y, int z) {
	e2[++cnt2] = (edge){y, head2[x], z}, head2[x] = cnt2;
	e2[++cnt2] = (edge){x, head2[y], z}, head2[y] = cnt2;
}
void build(int *p, int n) {
	if (n == 1) return;
	static int q1[N], q2[N];
	int p1 = 0, p2 = 0;
	int val = dinic(p[0], p[1]);
	addedge2(p[0], p[1], val);
	for (int i = 0; i < n; i++) {
		if (lv[p[i]])
			q1[p1++] = p[i];
		else
			q2[p2++] = p[i];
	}
	memcpy(p, q1, p1 << 2);
	memcpy(p + p1, q2, p2 << 2);
	if (p1) build(p, p1);
	if (p2) build(p + p1, p2);
}

int n, dep[N], par[K][N], mn[K][N];
void dfs2(int x, int p) {
	for (int i = head2[x]; i; i = e2[i].next) {
		int nx = e2[i].to;
		if (nx == p) continue;
		dep[nx] = dep[x] + 1;
		mn[0][nx] = e2[i].w;
		par[0][nx] = x;
		dfs2(nx, x);
	}
}
void init() {
	for (int i = 1; i < K; i++) {
		for (int j = 1; j <= n; j++) {
			par[i][j] = par[i - 1][par[i - 1][j]];
			mn[i][j] = std::min(mn[i - 1][j], mn[i - 1][par[i - 1][j]]);
		}
	}
}
int min(int x, int y) {
	int ret = INF;
	if (dep[x] > dep[y]) std::swap(x, y);
	int sub = dep[y] - dep[x];
	for (int i = K - 1; i >= 0; i--)
		if (sub & (1 << i)) ret = std::min(ret, mn[i][y]), y = par[i][y];
	if (x == y) return ret;
	for (int i = K - 1; i >= 0; i--) {
		if (par[i][x] != par[i][y]) {
			ret = std::min(ret, std::min(mn[i][x], mn[i][y]));
			x = par[i][x], y = par[i][y];
		}
	}
	return std::min(ret, std::min(mn[0][x], mn[0][y]));
}

int m, x, y, z, q, id[N];
int main() {
	for (scanf("%d%d", &n, &m); m--;) {
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z);
	}
	for (int i = 1; i <= n; i++) id[i - 1] = i;
	build(id, n);
	dep[1] = 1;
	dfs2(1, -1);
	init();
	for (scanf("%d", &q); q--;) {
		scanf("%d%d", &x, &y);
		printf("%d\n", min(x, y));
	}
}