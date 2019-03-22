#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e5 + 51, M = 1e6 + 61, K = 44, INF = 0x3f3f3f3f,
		  dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
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

int n, m, k, d, a[K][K][K];
int id(int lv, int x, int y) { return ((lv - 1) * n + x - 1) * m + y + 2; }
int main() {
	scanf("%d%d%d%d", &n, &m, &k, &d);
	for (int h = 1; h <= k; h++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%d", a[h][i] + j);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			addedge(1, id(1, i, j), a[1][i][j]);
			addedge(id(k, i, j), 2, INF);
			for (int h = 2; h <= k; h++) {
				addedge(id(h - 1, i, j), id(h, i, j), a[h][i][j]);
				if (h <= d) continue;
				for (int _ = 0; _ < 4; _++) {
					int x = i + dir[_][0], y = j + dir[_][1];
					if (x < 1 || y < 1 || x > n || y > m) continue;
					addedge(id(h, i, j), id(h - d, x, y), INF);
				}
			}
		}
	}
	printf("%d", dinic(1, 2));
}