#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e2 + 22, M = 2e5 + 52, INF = 0x3f3f3f3f;
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

int n, x, y, s, t, S, T;
int fl[N];
int main() {
	scanf("%d", &n);
	S = n + 1, T = n + 2, s = n + 3, t = n + 4;
	for (int i = 1; i <= n; i++) {
		addedge(s, i, INF);
		addedge(i, t, INF);
		for (scanf("%d", &x); x--;) {
			scanf("%d", &y);
			addedge(i, y, INF - 1);
			fl[i]--, fl[y]++;
		}
	}
	int tmp = cnt;
	addedge(t, s, INF);
	for (int i = 1; i <= n; i++) {
		if (fl[i] > 0) addedge(S, i, fl[i]);
		if (fl[i] < 0) addedge(i, T, -fl[i]);
	}
	dinic(S, T), x = e[tmp + 2].w;
	for (int i = tmp + 1; i <= cnt; i++) e[i].w = 0;
	printf("%d", x - dinic(t, s));
}