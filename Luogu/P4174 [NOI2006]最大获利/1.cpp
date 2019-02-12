#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e5 + 51, M = 1e6 + 61, INF = 0x3f3f3f3f;
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
int dinic(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}

int n, m, _, s, x, y, z;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		addedge(i + 2, 2, x);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z), s += z;
		addedge(1, i + n + 2, z);
		addedge(i + n + 2, x + 2, INF);
		addedge(i + n + 2, y + 2, INF);
	}
	printf("%d", s - dinic(1, 2));
}