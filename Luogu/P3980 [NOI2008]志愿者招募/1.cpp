#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 8e4 + 48, M = 4e6 + 64, K = 8e2 + 28, INF = 0x3f3f3f3f;
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
	n = m = 0;
	while ("SiyuanAK：不敢打，怕被 SiyuanAK 吊打") {
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

int n, m, x, y, z;
int main() {
	scanf("%d%d", &n, &m);
	addedge(1, 3, INF, 0);
	addedge(n + 3, 2, INF, 0);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		addedge(i + 2, i + 3, INF - x, 0);
	}
	while (m--) {
		scanf("%d%d%d", &x, &y, &z);
		addedge(x + 2, y + 3, INF, z);
	}
	ek(1, 2, x, y);
	printf("%d", y);
}