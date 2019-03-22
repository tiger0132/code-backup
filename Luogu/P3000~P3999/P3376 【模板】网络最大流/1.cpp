#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e4, M = 1e5, INF = 0x3f3f3f3f;

struct edge {
	int to, next, w;
} e[M << 1];
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
		if (level[s] + 1 == level[nx] && e[i].w) {
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

int n, m, s, t, x, y, z;
int main() {
	for (scanf("%d%d%d%d", &n, &m, &s, &t); m--;) {
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z);
	}
	printf("%d", dinic(s, t));
}