#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e2 + 22, M = 6e3 + 36, INF = 0x3f3f3f3f;

struct edge {
	int to, next, w;
} e[N << 2];
int head[N], cnt = 1;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z};
	head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0};
	head[y] = cnt;
}

int level[N];
bool bfs(int s, int t) {
	memset(level, 0, sizeof level);
	std::queue<int> q;
	q.push(s);
	level[s] = 1;
	while (!q.empty()) {
		int pos = q.front();
		q.pop();
		for (int i = head[pos]; i; i = e[i].next) {
			int nx = e[i].to;
			if (level[nx] || !e[i].w) continue;
			level[nx] = level[pos] + 1;
			q.push(nx);
		}
	}
	return level[t];
}

int dfs(int s, int t, int flow) {
	if (s == t) return flow;
	int ret = 0;
	for (int i = head[s]; flow && i; i = e[i].next) {
		int nx = e[i].to;
		if (level[nx] == level[s] + 1 && e[i].w) {
			int tmp = dfs(nx, t, std::min(flow, e[i].w));
			e[i].w -= tmp;
			e[i ^ 1].w += tmp;
			ret += tmp;
			flow -= tmp;
		}
	}
	if (!ret) level[s] = 0;
	return ret;
}

int dinic(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}

bool vis[N];
void dfs(int x) {
	if (vis[x]) return;
	printf("%d ", x >> 1);
	vis[x] = 1;
	for (int i = head[x]; i; i = e[i].next) {
		if (!e[i].w && (~i & 1)) return dfs(e[i].to - 1);
	}
}

int n, m, x, y;
int main() {
	for (scanf("%d%d", &n, &m); m--;) {
		scanf("%d%d", &x, &y);
		addedge(2 * x, 2 * y + 1, 1);
	}
	for (int i = 1; i <= n; i++) {
		addedge(1, 2 * i, 1);
		addedge(2 * i + 1, 2 * n + 2, 1);
	}
	x = dinic(1, 2 * n + 2);
	vis[2 * n + 2] = 1;
	for (int i = 1; i <= n; i++) {
		if (!vis[2 * i]) {
			dfs(2 * i);
			puts("");
		}
	}
	printf("%d", n - x);
}