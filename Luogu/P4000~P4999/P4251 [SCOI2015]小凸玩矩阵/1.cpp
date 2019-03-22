#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e3 + 31, M = 1e6 + 61, K = 3e2 + 23, INF = 0x3f3f3f3f;
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

int n, m, k, l, r, a[K][K];
int check(int x) {
	memset(head, 0, sizeof head), cnt = 1;
	for (int i = 1; i <= m; i++) addedge(i + n + 2, 2, 1);
	for (int i = 1; i <= n; i++) {
		addedge(1, i + 2, 1);
		for (int j = 1; j <= m; j++) {
			if (a[i][j] <= x) addedge(i + 2, j + n + 2, 1);
		}
	}
	return dinic(1, 2);
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	k = n - k + 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", a[i] + j);
		}
	}
	l = -1e9, r = 1e9;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid) >= k)
			r = mid;
		else
			l = mid + 1;
	}
	printf("%d", l);
}