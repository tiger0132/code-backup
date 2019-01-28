#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

typedef long long ll;
const int N = 1e5 + 51, M = 52;

struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z};
	head[x] = cnt;
	e[++cnt] = (edge){x, head[y], z};
	head[y] = cnt;
}

int dfn[N], dep[N], par[N], sz[N], son[N], top[N], idx;
ll d$[N];
void dfs1(int x, int p, int d) {
	par[x] = p, dep[x] = d, sz[x] = 1;
	int mx = 0;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		d$[nx] = d$[x] + e[i].w;
		dfs1(nx, x, d + 1);
		sz[x] += sz[nx];
		if (sz[nx] > mx) mx = sz[nx], son[x] = nx;
	}
}
void dfs2(int x, int t) {
	dfn[x] = ++idx, top[x] = t;
	if (!son[x]) return;
	dfs2(son[x], t);
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx != par[x] && nx != son[x]) dfs2(nx, nx);
	}
}
int lca(int x, int y) {
	for (; top[x] != top[y]; x = par[top[x]]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
	}
	return dep[x] < dep[y] ? x : y;
}

int p$[N];
int find(int x) { return p$[x] ? p$[x] = find(p$[x]) : x; }
void merge(int x, int y) {
	if ((x = find(x)) != (y = find(y))) p$[x] = y;
}

ll dis[M][N];
int vis[N];
void spfa(int id, int x) {
	memset(dis[id], 0x3f, sizeof dis[id]);
	std::queue<int> q;
	dis[id][x] = 0;
	q.push(x);
	while (!q.empty()) {
		int pos = q.front();
		vis[pos] = 0;
		q.pop();
		for (int i = head[pos]; i; i = e[i].next) {
			int nx = e[i].to;
			if (dis[id][nx] > dis[id][pos] + e[i].w) {
				dis[id][nx] = dis[id][pos] + e[i].w;
				if (!vis[nx]) {
					vis[nx] = 1;
					q.push(nx);
				}
			}
		}
	}
}

struct $ {
	int x, y, z, f;
	bool operator<(const $& rhs) const { return z < rhs.z; }
} ed[N];

int n, m, q, c, x, y;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &ed[i].x, &ed[i].y, &ed[i].z);
		addedge(ed[i].x, ed[i].y, ed[i].z);
	}
	std::sort(ed + 1, ed + m + 1);
	for (int i = 1; i <= m; i++) {
		if (find(ed[i].x) != find(ed[i].y))
			merge(ed[i].x, ed[i].y);
		else
			ed[i].f = 1;
	}
	for (int i = 1; i <= m; i++) {
		if (ed[i].f) {
			spfa(++c, ed[i].x);
			spfa(++c, ed[i].y);
		}
	}
	memset(head, 0, sizeof head);
	cnt = 0;
	for (int i = 1; i <= m; i++) {
		if (!ed[i].f) addedge(ed[i].x, ed[i].y, ed[i].z);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	for (scanf("%d", &q); q--;) {
		scanf("%d%d", &x, &y);
		ll ans = d$[x] + d$[y] - 2 * d$[lca(x, y)];
		for (int i = 1; i <= c; i++) {
			ans = std::min(ans, dis[i][x] + dis[i][y]);
		}
		printf("%I64d\n", ans);
	}
}