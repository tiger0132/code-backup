#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e3 + 31, M = 2e5 + 52, INF = 0x3f3f3f3f;
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
	q.push(s);
	lv[s] = 1;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
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
		if (lv[nx] != lv[s] + 1 || !e[i].w) continue;
		int tmp = dfs(nx, t, std::min(f, e[i].w));
		f -= tmp;
		r += tmp;
		e[i].w -= tmp;
		e[i ^ 1].w += tmp;
	}
	return r;
}
int dinic(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}

#define X(x) ((x) + 2)
#define Y(x) ((x) + n + 2)

int n, len, ans, a[N], dp[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	for (int i = 1; i <= n; len = std::max(len, dp[i++])) {
		for (int j = 0; j < i; j++) {
			if (a[j] <= a[i]) dp[i] = std::max(dp[i], dp[j] + 1);
		}
	}
	printf("%d\n", len);
	for (int i = 1; i <= n; i++) {
		addedge(X(i), Y(i), 1);
		if (dp[i] == 1) addedge(1, X(i), 1);
		if (dp[i] == len) addedge(Y(i), 2, 1);
		for (int j = 1; j < i; j++)
			if (a[j] <= a[i] && dp[j] + 1 == dp[i]) addedge(Y(j), X(i), 1);
	}
	printf("%d\n", ans = dinic(1, 2));
	addedge(1, X(1), INF), addedge(X(1), Y(1), INF);
	if (dp[n] == len) addedge(Y(n), 2, INF), addedge(X(n), Y(n), INF);
	printf("%d", ans + dinic(1, 2));
}