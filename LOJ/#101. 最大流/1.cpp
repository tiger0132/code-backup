#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

typedef long long ll;
const int N = 1e2 + 21, M = 5e3 + 35;
struct edge {
	int to, next, w;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, x[head], 0}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head], z}, y[head] = cnt;
}

int lv[N];
bool bfs(int s, int t) {
	memset(lv, 0, sizeof lv), s[lv] = 1;
	std::queue<int> q;
	for (q.push(s); !q.empty(); q.pop())
		for (int x = q.front(), i = x[head], nx; i; i = e[i].next)
			if (!(nx = e[i].to)[lv] && e[i ^ 1].w) q.push(nx), nx[lv] = x[lv] + 1;
	return t[lv];
}
int dfs(int s, int t, int f) {
	if (s == t || !f) return f;
	int r = 0;
	for (int i = s[head], nx, w; f && i; i = e[i].next)
		if ((nx = e[i].to)[lv] == s[lv] + 1 && e[i ^ 1].w)
			w = dfs(nx, t, std::min(f, e[i ^ 1].w)), e[i].w += w, e[i ^ 1].w -= w, r += w,
			f -= w;
	return (f && (s[lv] = 0)), r;
}
ll dinic(int s, int t) {
	ll r = 0;
	while (bfs(s, t)) r += dfs(s, t, 0x7fffffff);
	return r;
}

int n, m, s, t, x, y, z;
int main() {
	for (scanf("%d%d%d%d", &n, &m, &s, &t); m--;) {
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z);
	}
	printf("%lld", dinic(s, t));
}