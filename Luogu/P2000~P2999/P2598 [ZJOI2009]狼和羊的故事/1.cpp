#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e4 + 42, M = 4e5 + 54, K = 1e2 + 21, INF = 0x3f3f3f3f,
		  dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
struct edge {
	int to, next, w;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0}, head[y] = cnt;
}

int lv[M];
bool bfs(int s, int t) {
	memset(lv, 0, sizeof lv);
	std::queue<int> q;
	lv[s] = 1;
	for (q.push(s); !q.empty(); q.pop()) {
		int x = q.front();
		for (int i = head[x]; i; i = e[i].next) {
			int nx = e[i].to;
			if (lv[nx] || !e[i].w) continue;
			lv[nx] = lv[x] + 1;
			q.push(nx);
		}
	}
	return lv[t];
}
int dfs(int s, int t, int f) {
	if (s == t) return f;
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

int n, m, a[K][K];
int id(int x, int y) { return (x - 1) * m + y + 2; }
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", a[i] + j);
			if (a[i][j] == 1) addedge(1, id(i, j), INF);
			if (a[i][j] == 2) addedge(id(i, j), 2, INF);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 0; k < 4; k++) {
				int x = i + dir[k][0], y = j + dir[k][1];
				if (x < 1 || y < 1 || x > n || y > m) continue;
				addedge(id(i, j), id(x, y), 1);
			}
		}
	}
	printf("%d", dinic(1, 2));
}