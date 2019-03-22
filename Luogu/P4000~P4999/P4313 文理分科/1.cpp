#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 4e4 + 44, M = 4e5 + 54, K = 1e2 + 21, INF = 0x3f3f3f3f,
		  dir[5][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}};
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
	if (s == t) return f;
	int r = 0;
	for (int i = head[s]; f && i; i = e[i].next) {
		int nx = e[i].to;
		if (!e[i].w || lv[nx] != lv[s] + 1) continue;
		int tmp = dfs(nx, t, std::min(f, e[i].w));
		e[i].w -= tmp, e[i ^ 1].w += tmp;
		f -= tmp, r += tmp;
	}
	return r;
}
int dinic(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}

int n, m, _, x, s;
int id(int i, int j) { return (i - 1) * m + j + 2; }
int main() {
	scanf("%d%d", &n, &m);
	_ = id(n, m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &x), s += x;
			addedge(1, id(i, j), x);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &x), s += x;
			addedge(id(i, j), 2, x);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &x), s += x;
			addedge(1, ++_, x);
			for (int k = 0; k < 5; k++) {
				int nx = i + dir[k][0], ny = j + dir[k][1];
				if (1 <= nx && nx <= n && 1 <= ny && ny <= m) addedge(_, id(nx, ny), INF);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &x), s += x;
			addedge(++_, 2, x);
			for (int k = 0; k < 5; k++) {
				int nx = i + dir[k][0], ny = j + dir[k][1];
				if (1 <= nx && nx <= n && 1 <= ny && ny <= m) addedge(id(nx, ny), _, INF);
			}
		}
	}
	printf("%d", s -= dinic(1, 2));
}