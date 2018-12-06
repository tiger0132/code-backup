#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

struct edge {
	int from, to, next, capacity, flow, cost;
} e[200005];

int head[6003], cnt = 1;
int pre[6003];
int flow[6003];

void ek(int s, int t, int& rflow, int& cost) {
	int dis[6003];
	int vis[6003];
	queue<int> bfs;
	while (1) {
		memset(pre, 0, sizeof pre);
		memset(flow, 0, sizeof flow);
		memset(dis, 0x3f, sizeof dis);
		memset(vis, 0, sizeof vis);
		bfs.push(s);
		flow[s] = 0x3f3f3f3f;
		dis[s] = 0;
		while (!bfs.empty()) {
			int pos = bfs.front(); bfs.pop();
			vis[pos] = 0;
			for (int i = head[pos]; i; i = e[i].next) {
				int nx = e[i].to;
				if (e[i].flow < e[i].capacity && dis[nx] > dis[pos] + e[i].cost) {
					dis[nx] = dis[pos] + e[i].cost;
					flow[nx] = min(flow[pos], e[i].capacity - e[i].flow);
					pre[nx] = i;
					if (!vis[nx]) {
						bfs.push(nx);
						vis[nx] = 1;
					}
				}
			}
		}
		if (!pre[t]) break;
		for (int i = pre[t]; i; i = pre[e[i].from]) {
			e[i].flow += flow[t];
			e[i^1].flow -= flow[t];
		}
		rflow += flow[t];
		cost += dis[t] * flow[t];
	}
}

void addedge(int x, int y, int z, int w) {
	e[++cnt] = (edge){x, y, head[x], z, 0, w}; head[x] = cnt;
	e[++cnt] = (edge){y, x, head[y], 0, 0, -w}; head[y] = cnt;
}

int n, s, t, x, y, z, rflow, cost;
int rec[12][12];
// const int k = 2;
int k;

int id(int x, int y) {
	return n*(x-1) + y;
}

int main() {
	scanf("%d%d", &n, &k);
	s = 1, t = 2*n*n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", rec[i]+j);
			addedge(id(i, j), n*n + id(i, j), 1, -rec[i][j]);
			addedge(id(i, j), n*n + id(i, j), k - 1, 0);
			if (j < n) addedge(n*n + id(i, j), id(i, j + 1), k, 0);
			if (i < n) addedge(n*n + id(i, j), id(i + 1, j), k, 0);
		}
	}
	// while (~scanf("%d%d%d", &x, &y, &z) && (x || y || z)) {
	// 	rec[x-1][y-1] = z;
	// }
	ek(s, t, rflow, cost);
	printf("%d", -cost);
	return 0;
}