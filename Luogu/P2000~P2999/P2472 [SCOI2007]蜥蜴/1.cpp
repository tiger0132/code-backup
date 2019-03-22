#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e3 + 31, M = 1e5 + 51, K = 22, INF = 0x3f3f3f3f;
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
	q.push(s);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
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
		r += tmp, f -= tmp;
		e[i].w -= tmp, e[i ^ 1].w += tmp;
	}
	if (!f) lv[s] = 0;
	return r;
}
int dinic(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}

int n, m, d, s;
int id(int x, int y) { return ((x - 1) * m + y + 1) * 2; }

char a[K][K];
int main() {
	scanf("%d%d%d", &n, &m, &d);
	for (int i = 1; i <= n; i++) {
		scanf("%s", a[i] + 1);
		for (int j = 1; j <= m; j++) {
			if (a[i][j] -= 48) addedge(id(i, j), id(i, j) + 1, a[i][j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!a[i][j]) continue;
			for (int x = i - d; x <= i + d; x++) {
				for (int y = j - d; y <= j + d; y++) {
					if (abs(x - i) + abs(y - j) <= d && (x != i || y != j) && 1 <= x && x <= n && 1 <= y &&
						y <= m && a[x][y])
						addedge(id(i, j) + 1, id(x, y), INF);
				}
			}
			if (i <= d || j <= d || n - i < d || m - j < d) addedge(id(i, j) + 1, 2, INF);
		}
	}
	for (int i = 1; i <= n; i++) {
		scanf("%s", a[i] + 1);
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == 'L') s++, addedge(1, id(i, j), 1);
		}
	}
	printf("%d", s - dinic(1, 2));
}