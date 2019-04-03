#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e6 + 61, INF = 0x3f3f3f3f;
struct edge {
	int to, next, w;
} e[N * 8];
int head[N], cnt = 1;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], z}, head[y] = cnt;
}
int lv[N];
bool bfs(int s, int t) {
	memset(lv, 0, sizeof lv), lv[s] = 1;
	std::queue<int> q;
	for (q.push(s); !q.empty(); q.pop())
		for (int x = q.front(), i = head[x], nx; i; i = e[i].next)
			if (e[i].w && !lv[nx = e[i].to]) lv[nx] = lv[x] + 1, q.push(nx);
	return lv[t];
}
int dfs(int s, int t, int f) {
	if (s == t || !f) return f;
	int r = 0;
	for (int i = head[s], w; f && i; i = e[i].next)
		if (e[i].w && lv[e[i].to] == lv[s] + 1)
			w = dfs(e[i].to, t, std::min(f, e[i].w)), r += w, f -= w, e[i].w -= w, e[i ^ 1].w += w;
	return (f && (lv[s] = -1)), r;
}
int dinic(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}

int n, m, x;
int id(int x, int y) { return (x - 1) * m + y; }
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < m; j++) scanf("%d", &x), addedge(id(i, j), id(i, j + 1), x);
	for (int i = 1; i < n; i++)
		for (int j = 1; j <= m; j++) scanf("%d", &x), addedge(id(i, j), id(i + 1, j), x);
	for (int i = 1; i < n; i++)
		for (int j = 1; j < m; j++) scanf("%d", &x), addedge(id(i, j), id(i + 1, j + 1), x);
	printf("%d", dinic(id(1, 1), id(n, m)));
}