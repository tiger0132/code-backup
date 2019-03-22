#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 4e3 + 34, M = 1e5 + 51, INF = 0x3f3f3f3f;
struct edge {
	int to, next, w, c;
} e[M << 1];
int head[N], cnt = 1;
inline void addedge(int x, int y, int z, int w) {
	e[++cnt] = (edge){y, head[x], z, w}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0, -w}, head[y] = cnt;
}
inline void ek(int s, int t, int& n, int& m) {
	static int dis[N], vis[N], flow[N], pre[N];
	std::queue<int> q;
	n = m = 0;
	while (">_<") {
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
		if (dis[t] == 0x3f3f3f3f) return;
		for (int i = pre[t]; i; i = pre[e[i ^ 1].to]) {
			e[i].w -= flow[t];
			e[i ^ 1].w += flow[t];
		}
		n += flow[t];
		m += flow[t] * dis[t];
	}
}

int n, m, k;
inline int id(int x, int y, int z) { return ((x - 1) * m + y + 1) * 2 + z; }

void dfs(int p, int x) {
	if (x == id(n, m, 1)) return;
	for (int i = head[x]; i; i = e[i].next) {
		if (e[i ^ 1].w && x < e[i].to) {
			e[i ^ 1].w--;
			printf("%d %d\n", p, e[i].to - x == 1);
			return dfs(p, e[i].to + 1);
		}
	}
}

int x, y;
int main() {
	scanf("%d%d%d", &k, &m, &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &x);
			if (x & 1) continue;
			addedge(id(i, j, 0), id(i, j, 1), INF, 0);
			if (x) addedge(id(i, j, 0), id(i, j, 1), 1, -1);
			if (1 < i) addedge(id(i - 1, j, 1), id(i, j, 0), INF, 0);
			if (1 < j) addedge(id(i, j - 1, 1), id(i, j, 0), INF, 0);
		}
	}
	addedge(1, id(1, 1, 0), k, 0);
	addedge(id(n, m, 1), 2, k, 0);
	ek(1, 2, x, y);
	// return !printf("%d", -y);
	for (int i = 1; i <= k; i++) dfs(i, id(1, 1, 1));
}