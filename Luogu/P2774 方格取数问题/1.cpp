#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e4 + 42, M = 1e2 + 21,
		  dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}, INF = 0x3f3f3f3f;

struct edge {
	int to, next, w;
} e[N << 4];
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

int n, m, a[M][M];
int id(int x, int y) { return (x - 1) * m + y + 2; }

long long sum;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", a[i] + j);
			sum += a[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if ((i + j) & 1)
				addedge(1, id(i, j), a[i][j]);
			else
				addedge(id(i, j), 2, a[i][j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if ((i + j) & 1) {
				for (int k = 0; k < 4; k++) {
					int nx = i + dir[k][0], ny = j + dir[k][1];
					if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
					addedge(id(i, j), id(nx, ny), INF);
				}
			}
		}
	}
	printf("%lld", sum - dinic(1, 2));
}