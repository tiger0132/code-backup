#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e2 + 22, INF = 0x3f3f3f3f;

struct edge {
	int to, next, w, c;
} e[N * N * 4];
int head[N], cnt;
void addedge(int x, int y, int z, int w) {
	e[++cnt] = (edge){y, head[x], z, w};
	head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0, -w};
	head[y] = cnt;
}

void ek(int s, int t, int &mflow, int &mcost) {
	static int dis[N], vis[N], flow[N], pre[N];
	std::queue<int> q;
	mflow = mcost = 0;
	while (1) {
		memset(dis, 0x3f, sizeof dis);
		q.push(s);
		flow[s] = 0x3f3f3f3f;
		dis[s] = 0;
		while (!q.empty()) {
			int pos = q.front();
			vis[pos] = 0;
			q.pop();
			for (int i = head[pos]; i; i = e[i].next) {
				int nx = e[i].to;
				if (e[i].w && dis[nx] > dis[pos] + e[i].c) {
					dis[nx] = dis[pos] + e[i].c;
					flow[nx] = std::min(flow[pos], e[i].w);
					pre[nx] = i;
					if (!vis[nx]) {
						q.push(nx);
						vis[nx] = 1;
					}
				}
			}
		}
		if (dis[t] == 0x3f3f3f3f) return;
		for (int i = pre[t]; i; i = pre[e[i ^ 1].to]) {
			e[i].w -= flow[t];
			e[i ^ 1].w += flow[t];
		}
		mflow += flow[t];
		mcost += dis[t] * flow[t];
	}
}

int n, m, a[N], b[N], c[N][N];
void build(int off) {
	memset(head, 0, sizeof head);
	cnt = 1;
	for (int i = 1; i <= n; i++) {
		addedge(1, i + 1, a[i], 0);
		for (int j = 1; j <= m; j++) {
			addedge(i + 1, j + n + 1, INF, c[i][j] * off);
		}
	}
	for (int i = 1; i <= m; i++) {
		addedge(i + n + 1, n + m + 2, b[i], 0);
	}
}

int x, y;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", b + i);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", c[i] + j);
		}
	}
	build(1);
	ek(1, n + m + 2, x, y);
	printf("%d\n", y);
	build(-1);
	ek(1, n + m + 2, x, y);
	printf("%d", -y);
}