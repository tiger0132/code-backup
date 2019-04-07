// clang-format off
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e4 + 41, M = 1e5 + 51, INF = 0x3f3f3f3f;
struct edge {
	int to, next, w, c;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z, int w) {
	e[++cnt] = (edge){y, head[x], z, w}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0, -w}, head[y] = cnt;
}
void ek(int s, int t, int& n, int& m) {
	std::queue<int> q; static int dis[N], fl[N], pre[N], vis[N];
	for (n = m = 0; (memset(dis, 0x3f, sizeof dis), fl[s] = INF, dis[s] = 0), 1; n += fl[t], m += fl[t] * dis[t]) {
		for (q.push(s); !q.empty(); q.pop())
			for (int x = q.front(), i = head[x], nx = vis[x] = 0; i; i = e[i].next)
				if (dis[nx = e[i].to] > dis[x] + e[i].c && e[i].w) dis[nx] = dis[x] + e[i].c, pre[nx] = i,
					fl[nx] = std::min(fl[x], e[i].w), (vis[nx] || (q.push(nx), vis[nx] = 1));
		if (dis[t] == INF) return;
		for (int i = pre[t]; i; i = pre[e[i ^ 1].to]) e[i].w -= fl[t], e[i ^ 1].w += fl[t];
	}
}

int n, m, s, t, x, y, z, w;
int main() {
	for (scanf("%d%d%d%d", &n, &m, &s, &t); m--; ) {
		scanf("%d%d%d%d", &x, &y, &z, &w);
		addedge(x, y, z, w);
	}
	ek(s, t, x, y), printf("%d %d", x, y);
}