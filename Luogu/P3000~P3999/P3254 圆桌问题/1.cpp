#include <cstdio>
#include <cstring>
#include <queue>

const int N = 5e2 + 25, M = 6e4 + 46, INF = 0x3f3f3f3f;

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
	level[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int pos = q.front();
		q.pop();
		for (int i = head[pos]; i; i = e[i].next) {
			int nx = e[i].to;
			if (!e[i].w || level[nx]) continue;
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
			flow -= tmp;
			ret += tmp;
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

std::vector<int> vec[N];
int n, m, x, s;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		addedge(1, i + 2, x);
		s += x;
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", &x);
		addedge(n + i + 2, 2, x);
		for (int j = 1; j <= n; j++) {
			addedge(j + 2, n + i + 2, 1);
		}
	}
	if (dinic(1, 2) != s)
		return puts("0"), 0;
	else
		puts("1");
	for (int i = 2; i <= cnt; i += 2) {
		if (n + 2 < e[i].to && !e[i].w) {
			vec[e[i ^ 1].to - 2].push_back(e[i].to - n - 2);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j : vec[i]) {
			printf("%d ", j);
		}
		puts("");
	}
}