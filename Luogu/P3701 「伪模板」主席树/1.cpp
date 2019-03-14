#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e4 + 41, M = 1e5 + 51, INF = 0x3f3f3f3f;
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
			if (e[i].w && !lv[nx]) lv[nx] = lv[x] + 1, q.push(nx);
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
		int tmp = dfs(nx, t, std::min(e[i].w, f));
		e[i].w -= tmp, e[i ^ 1].w += tmp;
		r += tmp, f -= tmp;
	}
	if (f) lv[s] = -1;
	return r;
}
int dinic(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}

char a[N][9], b[N][9];
int va[N], vb[N];
int n, m, dx, dy;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", a[i]), dx += *a[i] == 'Y';
	for (int i = 1; i <= n; i++) scanf("%s", b[i]), dy += *b[i] == 'Y';
	for (int i = 1; i <= n; i++) scanf("%d", va + i);
	for (int i = 1; i <= n; i++) scanf("%d", vb + i);
	for (int i = 1; i <= n; i++) {
		addedge(1, i + 2, va[i] + (*a[i] == 'J') * dx);
		addedge(i + n + 2, 2, vb[i] + (*b[i] == 'J') * dy);
		for (int j = 1; j <= n; j++)
			if ((*a[i] == 'J' && strchr("WH", *b[j])) || (*a[i] == 'E' && strchr("JY", *b[j])) ||
				(*a[i] == 'Y' && strchr("HJ", *b[j])) || (*a[i] == 'H' && strchr("WE", *b[j])) ||
				(*a[i] == 'W' && strchr("YE", *b[j])))
				addedge(i + 2, j + n + 2, 1);
	}
	printf("%d", std::min(m, dinic(1, 2)));
}