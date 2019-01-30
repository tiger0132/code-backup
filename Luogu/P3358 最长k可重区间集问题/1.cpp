#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e3 + 32, M = 2e6 + 62, INF = 0x3f3f3f3f;

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

int n, k, x, y, l[N], r[N];
int t[N], _;

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", l + i, r + i);
		t[++_] = l[i], t[++_] = r[i];
	}
	std::sort(t + 1, t + _ + 1);
	addedge(1, 2, k, 0);
	for (int i = 1; i <= _; i++) {
		addedge(i + 1, i + 2, INF, 0);
	}
	for (int i = 1; i <= n; i++) {
		l[i] = std::lower_bound(t + 1, t + _ + 1, l[i]) - t;
		r[i] = std::lower_bound(t + 1, t + _ + 1, r[i]) - t;
		addedge(l[i] + 1, r[i] + 1, 1, t[l[i]] - t[r[i]]);  // 相反数
	}
	ek(1, _ + 2, x, y);
	printf("%d", -y);
}