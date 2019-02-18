#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e4 + 41, M = 1e6 + 61, INF = 0x3f3f3f3f;
struct edge {
	int to, next, w;
} e_[2][M << 1];
int h_[2][N], c_[2] = {1, 1};
edge *e = e_[0], *e2 = e_[1];
int *head = h_[0], *h2 = h_[1];

template <int id>
void addedge(int x, int y, int z) {
	e_[id][++c_[id]] = (edge){y, h_[id][x], z}, h_[id][x] = c_[id];
	if (!id) e_[id][++c_[id]] = (edge){x, h_[id][y], 0}, h_[id][y] = c_[id];
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

int n, m, v[N];
int id(int x, int y) { return (x - 1) * m + y + 2; }

int s, t, x, y, dgr[N];
std::queue<int> q;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &x);
			if (x > 0)
				s += x, addedge<0>(1, id(i, j), x);
			else
				addedge<0>(id(i, j), 2, -x);
			if (j < m) addedge<1>(id(i, j + 1), id(i, j), 0), dgr[id(i, j)]++;
			for (scanf("%d", &t); t--; dgr[id(x, y)]++) {
				scanf("%d%d", &x, &y);
				addedge<1>(id(i, j), id(++x, ++y), 0);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!dgr[id(i, j)]) q.push(id(i, j));
		}
	}
	for (; !q.empty(); q.pop()) {
		v[x = q.front()] = 1;
		for (int i = h2[x]; i; i = e2[i].next)
			if (!--dgr[e2[i].to]) q.push(e2[i].to);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!v[id(i, j)]) {
				addedge<0>(id(i, j), 2, INF);
				continue;
			}
			for (int k = h2[id(i, j)]; k; k = e2[k].next) addedge<0>(e2[k].to, id(i, j), INF);
		}
	}
	printf("%d", s - dinic(1, 2));
}