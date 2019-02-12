#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define F(x, y) for (int x = 1; x <= y; x++)
#define F2(x, y, z) for (int x = y; x <= z; x++)

const int N = 2e5 + 52, M = 4e6 + 64, K = 1e2 + 21, INF = 0x3f3f3f3f, dir[2][2] = {{1, 0}, {1, 0}};
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

int n, m, _, s, x, c[K][K];
int id(int i, int j) { return (i - 1) * m + j + 2; }
int main() {
	scanf("%d%d", &n, &m);
	_ = id(n, m);
	F(i, n) F(j, m) {
		scanf("%d", &x), s += x;
		addedge(1, id(i, j), x);
	}
	F(i, n) F(j, m) {
		scanf("%d", &x), s += x;
		addedge(id(i, j), 2, x);
	}
	F(i, n) F(j, m) scanf("%d", c[i] + j);
	F(i, n) F(j, m) F2(k, 0, 1) {
		int x = i + dir[k][0], y = j + dir[k][1];
		if (x < 1 || y < 1 || x > n || y > m) continue;
		s += 2 * (c[i][j] + c[x][y]);
		addedge(1, ++_, c[i][j] + c[x][y]);
		addedge(++_, 2, c[i][j] + c[x][y]);
		addedge(id(i, j), _, INF);
		addedge(id(x, y), _, INF);
	}
	printf("%d", s - dinic(1, 2));
}