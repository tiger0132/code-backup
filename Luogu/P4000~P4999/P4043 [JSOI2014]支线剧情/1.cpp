#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e3 + 31, M = 1e5 + 51, INF = 0x3f3f3f3f;
struct edge {
	int to, next, w, c;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z, int w) {
	e[++cnt] = (edge){y, head[x], z, w}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0, -w}, head[y] = cnt;
}
void ek(int s, int t, int& n, int& m) {
	static int dis[N], pre[N], flow[N], vis[N];
	std::queue<int> q;
	n = m = 0;
	while (1) {
		memset(dis, 0x3f, sizeof dis);
		flow[s] = INF, dis[s] = 0;
		for (q.push(s); !q.empty(); q.pop()) {
			int x = q.front();
			vis[x] = 0;
			for (int i = head[x]; i; i = e[i].next) {
				int nx = e[i].to;
				if (e[i].w && dis[nx] > dis[x] + e[i].c) {
					dis[nx] = dis[x] + e[i].c;
					flow[nx] = std::min(flow[x], e[i].w);
					pre[nx] = i;
					if (!vis[nx]) q.push(nx), vis[nx] = 1;
				}
			}
		}
		if (dis[t] == INF) return;
		for (int i = pre[t]; i; i = pre[e[i ^ 1].to]) e[i].w -= flow[t], e[i ^ 1].w += flow[t];
		n += flow[t];
		m += flow[t] * dis[t];
	}
}

int n, k, x, y, tot, dgr[N];
int main() {
	scanf("%d", &n);
	for (int i = 3; i <= n + 2; i++) {
		scanf("%d", &k);
		for (int j = 1; j <= k; j++) {
			scanf("%d%d", &x, &y), x += 2;
			// addedge(1, x, 1, y); 会 T
			tot += y, dgr[i]++, dgr[x]--;
			addedge(i, x, INF, y);
		}
		// addedge(i, 2, k, 0);
		if (i > 3) addedge(i, 3, INF, 0);  // 反悔边
	}
	for (int i = 3; i <= n + 2; i++) {
		if (dgr[i] > 0) addedge(i, 2, dgr[i], 0);
		if (dgr[i] < 0) addedge(1, i, -dgr[i], 0);
	}
	ek(1, 2, x, y);
	printf("%d", y + tot);
}