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
	static int dis[N], vis[N], pre[N], flow[N];
	std::queue<int> q;
	n = m = 0;
	while ("人类的本质是共鸣者，世间之行动乃同道哉") {
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

int n, m;
int id(int x, int y) { return (x - 1) * m + y + m + 2; }
int x, y;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		addedge(1, i + 2, 1, 0);
		for (int j = 1; j <= n; j++) {
			addedge(id(j, i), 2, 1, 0);
			scanf("%d", &x);
			for (int k = 1; k <= m; k++) {
				addedge(i + 2, id(j, k), 1, x * k);
			}
		}
	}
	ek(1, 2, x, y);
	printf("%.2f", y * 1. / m);
}