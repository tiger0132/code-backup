#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e3 + 31, M = 1e4 + 41, INF = 0x3f3f3f3f;
struct edge {
	int to, next, w, c;
} e[M << 1];
int head[N], cnt = 1;
inline void addedge(int x, int y, int z, int w) {
	e[++cnt] = (edge){y, head[x], z, w}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0, -w}, head[y] = cnt;
}
inline void ek(int s, int t, int& n, int& m) {
	static int vis[N], dis[N], flow[N], pre[N];
	std::queue<int> q;
	n = m = 0;
	while ("QwQ") {
		memset(dis, 0x3f, sizeof dis);
		flow[s] = INF;
		dis[s] = 0;
		q.push(s);
		while (!q.empty()) {
			int x = q.front();
			vis[x] = 0;
			q.pop();
			for (int i = head[x]; i; i = e[i].next) {
				int nx = e[i].to;
				if (e[i].w && dis[nx] > dis[x] + e[i].c) {
					dis[nx] = dis[x] + e[i].c;
					flow[nx] = std::min(flow[x], e[i].w);
					pre[nx] = i;
					if (!vis[nx]) vis[nx] = 1, q.push(nx);
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

int n, m;
inline int id(int x, int y) { return x * 20 + y + 3; }

int a, b, x, y, z;
int main() {
	scanf("%d%d%d%d", &a, &b, &n, &m);
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &x);
			addedge(id(i, j), id(i, j + 1), 1, -x);
			addedge(id(i, j), id(i, j + 1), INF, 0);
		}
	}
	for (int j = 0; j <= m; j++) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			addedge(id(i, j), id(i + 1, j), 1, -x);
			addedge(id(i, j), id(i + 1, j), INF, 0);
		}
	}
	for (; a--; addedge(1, id(y, z), x, 0)) scanf("%d%d%d", &x, &y, &z);
	for (; b--; addedge(id(y, z), 2, x, 0)) scanf("%d%d%d", &x, &y, &z);
	ek(1, 2, x, y);
	printf("%d", -y);
}