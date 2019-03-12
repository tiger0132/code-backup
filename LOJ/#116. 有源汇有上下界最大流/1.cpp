#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e2 + 22, M = 4e4 + 44, INF = 0x3f3f3f3f;
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

int n, m, s, t, x, y, z, w;
int fl[N], sum;

int main() {
	scanf("%d%d%d%d", &n, &m, &s, &t);
	addedge(t + 2, s + 2, INF);
	while (m--) {
		scanf("%d%d%d%d", &x, &y, &z, &w);
		addedge(x + 2, y + 2, w - z);
		fl[x] -= z, fl[y] += z;
	}
	for (int i = 1; i <= n; i++) {
		if (fl[i] > 0) addedge(1, i + 2, fl[i]), sum += fl[i];
		if (fl[i] < 0) addedge(i + 2, 2, -fl[i]);
	}
	if (dinic(1, 2) < sum) return puts("please go home to sleep"), 0;
	printf("%d", dinic(s + 2, t + 2));
}