#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e2 + 21, M = 1e5 + 51, K = 52, INF = 0x3f3f3f3f;
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
	q.push(s);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
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
	if (s == t) return f;
	int r = 0;
	for (int i = head[s]; f && i; i = e[i].next) {
		int nx = e[i].to;
		if (!e[i].w || lv[nx] != lv[s] + 1) continue;
		int tmp = dfs(nx, t, std::min(f, e[i].w));
		r += tmp, f -= tmp;
		e[i].w -= tmp, e[i ^ 1].w += tmp;
	}
	if (!f) lv[s] = 0;
	return r;
}
int dinic(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}

int n, a1, a2, an, b1, b2, bn;
char buf[K][K];
bool solve() {
	memset(head, 0, sizeof head), cnt = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (buf[i][j] == 'N') addedge(i + 2, j + 2, INF);
			if (buf[i][j] == 'O') addedge(i + 2, j + 2, 2);
		}
	}
	addedge(1, a1 + 2, an), addedge(1, b1 + 2, bn);
	addedge(a2 + 2, 2, an), addedge(b2 + 2, 2, bn);
	return dinic(1, 2) == an + bn;
}
int main() {
	while (~scanf("%d%d%d%d%d%d%d", &n, &a1, &a2, &an, &b1, &b2, &bn)) {
		a1++, a2++, b1++, b2++, an <<= 1, bn <<= 1;
		for (int i = 1; i <= n; i++) scanf("%s", buf[i] + 1);
		puts(solve() && (std::swap(b1, b2), solve()) ? "Yes" : "No");
	}
}