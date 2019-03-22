#include <cstdio>
#include <cstring>
#include <queue>

const int N = 5e3 + 35, M = 5e4 + 45;

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

int n, m, s, t, x, y, z, w;
int main() {
	for (scanf("%d%d%d%d", &n, &m, &s, &t); m--;) {
		scanf("%d%d%d%d", &x, &y, &z, &w);
		addedge(x, y, z, w);
	}
	ek(s, t, x, y);
	printf("%d %d", x, y);
}