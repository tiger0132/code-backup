#include <cstdio>
#include <cstring>
#include <queue>

typedef long long ll;
const int N = 4e3 + 34, M = 2e4 + 42, INF = 0x3f3f3f3f;
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

void ek(int s, int t, int& mflow, ll& mcost) {
	int dis[N], vis[N], flow[N], pre[N];
	std::queue<int> q;
	mflow = mcost = 0;
	while (1) {
		memset(dis, 0x3f, sizeof dis);
		q.push(s);
		dis[s] = 0;
		flow[s] = INF;
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
		mflow += flow[t];
		mcost += dis[t] * flow[t];
	}
}

int n, x, a, b, c, d, _;
ll y;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		addedge(1, i + 2, x, 0);
		addedge(n + i + 2, 2, x, 0);
	}
	scanf("%d%d%d%d%d", &a, &b, &c, &d, &_);
	for (int i = 1; i <= n; i++) {
		addedge(1, i + n + 2, INF, a);
		if (i < n) addedge(i + 2, i + 3, INF, 0);
		if (i + b <= n) addedge(i + 2, i + n + b + 2, INF, c);
		if (i + d <= n) addedge(i + 2, i + n + d + 2, INF, _);
	}
	ek(1, 2, x, y);
	printf("%lld", y);
}