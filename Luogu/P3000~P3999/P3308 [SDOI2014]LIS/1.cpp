#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#define L(x) ((x) + 2)
#define R(x) ((x) + n + 2)

const int N = 2e3 + 32, M = 2e6 + 62, INF = 0x3f3f3f3f;
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

int a[N], b[N], c[N], dp[N], id[N], out[N], top;
int t, n, len, ans;
int main() {
	for (scanf("%d", &t); t--;) {
		memset(head, 0, sizeof head);
		memset(dp, 0, sizeof dp);
		cnt = 1, len = top = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", a + i), id[i] = i;
		for (int i = 1; i <= n; i++) scanf("%d", b + i), addedge(L(i), R(i), b[i]);
		for (int i = 1; i <= n; i++) scanf("%d", c + i);
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < i; j++)
				if (a[j] < a[i]) len = std::max(len, dp[i] = std::max(dp[i], dp[j] + 1));
			for (int j = 1; j < i; j++)
				if (a[j] < a[i] && dp[j] + 1 == dp[i]) addedge(R(j), L(i), INF);
			if (dp[i] == 1) addedge(1, L(i), INF);
		}
		for (int i = 1; i <= n; i++)
			if (dp[i] == len) addedge(R(i), 2, INF);
		ans = dinic(1, 2);
		std::sort(id + 1, id + n + 1, [](int x, int y) { return c[x] < c[y] || (c[x] == c[y] && x < y); });
		for (int i = 1; i <= n; i++) {
			int j = id[i] * 2;
			if (!e[j].w && !bfs(e[j ^ 1].to, e[j].to)) {
				e[j ^ 1].w = 0;
				dinic(e[j ^ 1].to, 1);
				dinic(2, e[j].to);
				out[++top] = id[i];
			}
		}
		printf("%d %d\n", ans, top);
		std::sort(out + 1, out + top + 1);
		for (int i = 1; i <= top; i++) printf("%d ", out[i]);
		puts("");
	}
}