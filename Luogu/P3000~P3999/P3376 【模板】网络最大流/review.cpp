// clang-format off
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e4 + 41, M = 1e5 + 51, INF = 0x3f3f3f3f;
struct edge {
	int to, next, w;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0}, head[y] = cnt;
}
int lv[N];
bool bfs(int s, int t) {
	std::queue<int> q; memset(lv, 0, sizeof lv), lv[s] = 1;
	for (q.push(s); !q.empty(); q.pop())
		for (int x = q.front(), i = head[x], nx; i; i = e[i].next)
			if (e[i].w && !lv[nx = e[i].to]) lv[nx] = lv[x] + 1, q.push(nx);
	return lv[t];
}
int dfs(int s, int t, int f) {
	if (s == t || !f) return f; int r = 0;
	for (int i = head[s], w; f && i; i = e[i].next)
		if (e[i].w && lv[e[i].to] == lv[s] + 1)
			w = dfs(e[i].to, t, std::min(f, e[i].w)), r += w, f -= w, e[i].w -= w, e[i ^ 1].w += w;
	return (f && (lv[s] = -1)), r;
}
int dinic(int s, int t) { int r = 0; while (bfs(s, t)) r += dfs(s, t, INF); return r; }

int n, m, s, t, x, y, z;
int main() {
	for (scanf("%d%d%d%d", &n, &m, &s, &t); m--; ) {
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z);
	}
	printf("%d", dinic(s, t));
}