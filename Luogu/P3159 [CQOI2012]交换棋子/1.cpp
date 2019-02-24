#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 3e4 + 43, M = 5e4 + 45, K = 33, INF = 0x3f3f3f3f;
struct edge {
	int to, next, w, c;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z, int w) {
	e[++cnt] = (edge){y, head[x], z, w}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0, -w}, head[y] = cnt;
}
void ek(int s, int t, int& n, int& m) {
	static int dis[N], vis[N], pre[N], flow[N];
	std::queue<int> q;
	while ("sro memset0 orz") {
		memset(dis, 0x3f, sizeof dis);
		flow[s] = INF, dis[s] = 0;
		for (q.push(s); !q.empty(); q.pop()) {
			int x = q.front();
			vis[x] = 0;
			for (int i = head[x]; i; i = e[i].next) {
				int nx = e[i].to;
				if (e[i].w && dis[nx] > dis[x] + e[i].c) {
					flow[nx] = std::min(flow[x], e[i].w);
					dis[nx] = dis[x] + e[i].c;
					pre[nx] = i;
					if (!vis[nx]) q.push(nx), vis[nx] = 1;
				}
			}
		}
		if (dis[t] == INF) return;
		for (int i = pre[t]; i; i = pre[e[i ^ 1].to]) {
			e[i].w -= flow[t];
			e[i ^ 1].w += flow[t];
		}
		n += flow[t];
		m += flow[t] * dis[t];
	}
}

char a[K][K], b[K][K], c[K][K];
int n, m, c1, c2, _;
template <int lv>
int id(int x, int y) {
	return ((x - 1) * m + y) * 3 + lv;
}  // 0 <= z <= 2
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
	for (int i = 1; i <= n; i++) scanf("%s", b[i] + 1);
	for (int i = 1; i <= n; i++) scanf("%s", c[i] + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			c[i][j] -= 48;
			if (a[i][j] -= 48) addedge(1, id<1>(i, j), 1, 0), c1++;
			if (b[i][j] -= 48) addedge(id<1>(i, j), 2, 1, 0), c2++;
			addedge(id<0>(i, j), id<1>(i, j), (c[i][j] + (!a[i][j] && b[i][j])) / 2, 0);
			addedge(id<1>(i, j), id<2>(i, j), (c[i][j] + (a[i][j] && !b[i][j])) / 2, 0);
			for (int x = std::max(1, i - 1); x <= std::min(n, i + 1); x++)
				for (int y = std::max(1, j - 1); y <= std::min(m, j + 1); y++)
					if (i != x || j != y) addedge(id<2>(i, j), id<0>(x, y), INF, 1);
		}
	}
	int x = 0, y = 0;
	ek(1, 2, x, y);
	printf(x == c1 && c1 == c2 ? "%d" : "-1", y);
}