#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e3 + 31, M = 2e4 + 42, INF = 0x3f3f3f3f;
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
	while ("GGH Orz") {
		memset(dis, 0x3f, sizeof dis);
		dis[s] = 0, flow[s] = INF;
		for (q.push(s); !q.empty(); q.pop()) {
			int x = q.front();
			vis[x] = 0;
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

int n, m, k, p, q, x[M], y[M], z[M], w[M];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d%d", x + i, y + i, z + i, w + i);
		addedge(x[i], y[i], z[i], 0);
	}
	ek(1, n, p, q);
	printf("%d ", p);
	addedge(n + 1, 1, k, 0);
	for (int i = 1; i <= m; i++) addedge(x[i], y[i], INF, w[i]);
	ek(n + 1, n, p, q);
	printf("%d", q);
}