#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>

const int N = 2e2 + 22, M = 3e3 + 33, INF = 0x3f3f3f3f;

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

int ans[N][N];
void dfs2(int s, int t, int p, int mn) {
	ans[s][t] = mn;
	for (int i = head2[t]; i; i = e2[i].next)
		if (e2[i].to != p) dfs2(s, e2[i].to, t, std::min(mn, e2[i].w));
}

int _, n, m, x, y, z, q, id[N];
int main() {
	for (scanf("%d", &_); _--;) {
		memset(head, 0, sizeof head), cnt = 1;
		memset(head2, 0, sizeof head2), cnt2 = 1;
		for (scanf("%d%d", &n, &m); m--;) {
			scanf("%d%d%d", &x, &y, &z);
			addedge(x, y, z);
		}
		for (int i = 1; i <= n; i++) id[i - 1] = i;
		build(id, n);
		for (int i = 1; i <= n; i++) dfs2(i, i, -1, INF);
		for (scanf("%d", &q); q--;) {
			scanf("%d", &x);
			int lans = 0;
			for (int i = 1; i < n; i++)
				for (int j = i + 1; j <= n; j++) lans += ans[i][j] <= x;
			printf("%d\n", lans);
		}
		if (_) puts("");
	}
}