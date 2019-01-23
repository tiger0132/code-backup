#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e2 + 22, M = 2e4 + 42;
struct edge {
	int to, next, w, c;
} e[M << 1];
int head[N], cnt = 1;
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

int n, x, y, c[N][N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		addedge(1, i + 2, 1, 0);
		addedge(n + i + 2, 2, 1, 0);
		for (int j = 1; j <= n; j++) {
			scanf("%d", c[i] + j);
			addedge(i + 2, n + j + 2, 1, c[i][j]);
		}
	}
	ek(1, 2, x, y);
	printf("%d\n", y);
	memset(head, 0, sizeof head);
	cnt = 1;
	for (int i = 1; i <= n; i++) {
		addedge(1, i + 2, 1, 0);
		addedge(n + i + 2, 2, 1, 0);
		for (int j = 1; j <= n; j++) {
			addedge(i + 2, n + j + 2, 1, -c[i][j]);
		}
	}
	ek(1, 2, x, y);
	printf("%d", -y);
}