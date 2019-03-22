#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

const int N = 1e3 + 31, M = 4e4 + 44, K = 55, INF = 0x3f3f3f3f;
struct edge {
	int to, next, w;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0}, head[y] = cnt;
}

int lv[N];
int bfs(int s, int t) {
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
	if (!r) lv[s] = 0;
	return r;
}
int dinic(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}

int par[K];
int f(int x) { return par[x] ? par[x] = f(par[x]) : x; }
inline void g(int x, int y) {
	if ((x = f(x)) != (y = f(y))) par[x] = y;
}

int n, m, k, x, y, ans, c[K], h[K];
std::vector<int> v[K];
inline int id(int t, int i) { return t * n + i + 1; }
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; i++) {
		for (scanf("%d%d", h + i, &x), c[i] = x; x--;) {
			scanf("%d", &y);
			v[i].push_back(y += 2);
			g(v[i].front(), v[i].back());
		}
	}
	if (f(1) != f(2)) return puts("0"), 0;
	n += 2;
	addedge(1, 3, k);
	for (int t = 1;; t++) {
		for (int i = 1; i <= n; i++) addedge(id(t - 1, i), id(t, i), INF);
		for (int j = 1; j <= m; j++)
			addedge(id(t - 1, v[j][(t - 1 + c[j]) % c[j]]), id(t, v[j][t % c[j]]), h[j]);
		if ((ans += dinic(1, id(t, 1))) == k) {
			return !printf("%d", t);
		}
	}
}