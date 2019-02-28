#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>

const int N = 2e3 + 32, M = 2e6 + 62, INF = 0x3f3f3f3f;

struct edge {
	int to, next, w;
} e[M << 1];
int n, head[N], cnt = 1;
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

std::set<int> s;
void build(int *p, int n) {
	if (n == 1) return;
	static int q1[N], q2[N];
	int p1 = 0, p2 = 0;
	int val = dinic(p[0], p[1]);
	s.insert(val);
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

int m, x, y, z, q, id[N];
int main() {
	for (scanf("%d%d", &n, &m); m--;) {
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z);
	}
	for (int i = 1; i <= n; i++) id[i - 1] = i;
	build(id, n);
	printf("%d", s.size());
}