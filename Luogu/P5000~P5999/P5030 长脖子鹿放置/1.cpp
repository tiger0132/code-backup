#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e5 + 51, M = 5e5 + 55, K = 2e2 + 22, INF = 0x3f3f3f3f,
		  dir[8][2] = {{1, 3}, {1, -3}, {-1, 3}, {-1, -3}, {3, 1}, {-3, 1}, {3, -1}, {-3, -1}};
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

int n, m, k;
int id(int x, int y) { return m * (x - 1) + y + 2; }

bool f[K][K];
int x, y;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= k; i++, f[x][y] = true) scanf("%d%d", &x, &y);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (f[i][j]) continue;
			if (~i % 2)
				addedge(id(i, j), 2, 1);
			else {
				addedge(1, id(i, j), 1);
				for (int t = 0; t < 8; t++) {
					int nx = i + dir[t][0], ny = j + dir[t][1];
					if (1 <= nx && nx <= n && 1 <= ny && ny <= m && !f[nx][ny]) addedge(id(i, j), id(nx, ny), 1);
				}
			}
		}
	printf("%d", n * m - dinic(1, 2) - k);
}