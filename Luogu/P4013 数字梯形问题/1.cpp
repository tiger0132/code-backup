#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 4e3 + 34, M = 2e5 + 52, K = 52, INF = 0x3f3f3f3f;

struct edge {
	int to, next, w, c;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z, int w) {
	e[++cnt] = (edge){y, head[x], z, w}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0, -w}, head[y] = cnt;
}

void ek(int s, int t, int& n, int& m) {
	static int dis[N], vis[N], flow[N], pre[N];
	std::queue<int> q;
	n = m = 0;
	while (1) {
		memset(dis, 0x3f, sizeof dis);
		flow[s] = INF, dis[s] = 0;
		for (q.push(s); !q.empty();) {
			int x = q.front();
			vis[x] = 0;
			q.pop();
			for (int i = head[x]; i; i = e[i].next) {
				int nx = e[i].to;
				if (e[i].w && dis[nx] > dis[x] + e[i].c) {
					dis[nx] = dis[x] + e[i].c;
					flow[nx] = std::min(flow[x], e[i].w);
					pre[nx] = i;
					if (!vis[nx]) {
						vis[nx] = 1;
						q.push(nx);
					}
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

int m, n, x, y, a[K][K], id[K][K], _ = 1;
int main() {
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < m + i; j++) {
			scanf("%d", a[i] + j);
			id[i][j] = _ += 2;
		}
	}
	for (int i = 1; i <= m; i++) addedge(1, id[1][i], 1, 0);
	for (int i = 1; i <= n + m; i++) addedge(id[n][i] + 1, 2, 1, 0);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < m + i; j++) {
			addedge(id[i][j], id[i][j] + 1, 1, -a[i][j]);
			if (i < n) {
				addedge(id[i][j] + 1, id[i + 1][j], 1, 0);
				addedge(id[i][j] + 1, id[i + 1][j + 1], 1, 0);
			}
		}
	}
	ek(1, 2, x, y);
	printf("%d\n", -y);

	for (int i = 2; i <= cnt; i += 2) e[i].w += e[i ^ 1].w, e[i ^ 1].w = 0;
	for (int i = 1; i <= n + m; i++) addedge(id[n][i] + 1, 2, 0x3f3f3f3f, 0);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < m + i; j++) {
			addedge(id[i][j], id[i][j] + 1, 0x3f3f3f3f, -a[i][j]);
		}
	}
	ek(1, 2, x, y);
	printf("%d\n", -y);

	for (int i = 2; i <= cnt; i += 2) e[i].w += e[i ^ 1].w, e[i ^ 1].w = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < m + i; j++) {
			if (i < n) {
				addedge(id[i][j] + 1, id[i + 1][j], INF, 0);
				addedge(id[i][j] + 1, id[i + 1][j + 1], INF, 0);
			}
		}
	}
	ek(1, 2, x, y);
	printf("%d", -y);
}