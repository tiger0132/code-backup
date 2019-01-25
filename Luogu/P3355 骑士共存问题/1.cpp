#include <cstdio>
#include <cstring>
#include <queue>

const int N = 4e4 + 44, M = 4e5 + 54, K = 2e2 + 22, INF = 0x3f3f3f3f,
		  dir[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
					   {1, -2},  {1, 2},  {2, -1},  {2, 1}};

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

int n;
int id(int x, int y) { return (x - 1) * n + y + 2; }

int m, x, y, _[K][K];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &x, &y);
		_[x][y] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (_[i][j]) continue;
			if (~(i + j) & 1) {
				addedge(id(i, j), 2, 1);
				continue;
			}
			addedge(1, id(i, j), 1);
			for (int k = 0; k < 8; k++) {
				int nx = i + dir[k][0], ny = j + dir[k][1];
				if (nx < 1 || ny < 1 || nx > n || ny > n || _[nx][ny]) continue;
				addedge(id(i, j), id(nx, ny), 1);
			}
		}
	}
	printf("%d", n * n - m - dinic(1, 2));
}