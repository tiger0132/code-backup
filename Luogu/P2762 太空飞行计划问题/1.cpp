#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

const int N = 2e2 + 22, M = 1e4 + 41;

struct edge {
	int to, next, w;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0}, head[y] = cnt;
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
			flow -= tmp;
			ret += tmp;
			e[i].w -= tmp;
			e[i ^ 1].w += tmp;
		}
	}
	return ret;
}
int dinic(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, 0x3f3f3f3f);
	return ret;
}

int n, m, x, s, t, sum, f;
char buf[' '];

int main() {
	scanf("%d%d", &n, &m);
	s = n + m + 1, t = n + m + 2;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		addedge(s, i, x);
		sum += x;
		std::cin.getline(buf, ' ');
		for (int j = 0; ~sscanf(buf + j, "%d", &x); j++) {
			j += !x;
			addedge(i, n + x, 0x3f3f3f3f);
			for (j += !x; x; x /= 10) j++;
		}
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", &x);
		addedge(n + i, t, x);
	}
	sum -= dinic(s, t);
	for (int i = 1; i <= n; i++) {
		if (level[i]) printf("%d ", i);
	}
	puts("");
	for (int i = 1; i <= m; i++) {
		if (level[n + i]) printf("%d ", i);
	}
	printf("\n%d", sum);
}