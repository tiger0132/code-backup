#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#define y1 asda123x6

typedef long long ll;
const int N = 1e4 + 41, INF = 0x3f3f3f3f;

struct edge {
	int to, next, w, c;
} e[N << 3];
int head[N], cnt = 1;
void addedge(int x, int y, int z, int w) {
	e[++cnt] = (edge){y, head[x], z, w}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0, -w}, head[y] = cnt;
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

int n, k, x, y, _, x1[N], y1[N], x2[N], y2[N], len[N], b[N];
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d%d", x1 + i, y1 + i, x2 + i, y2 + i);
		b[++_] = x1[i], b[++_] = y1[i], b[++_] = x2[i], b[++_] = y2[i];
		len[i] = sqrt(ll(x1[i] - x2[i]) * (x1[i] - x2[i]) + ll(y1[i] - y2[i]) * (y1[i] - y2[i]));
	}
	std::sort(b + 1, b + _ + 1);
	for (int i = 1; i <= n; i++) {
		x1[i] = std::lower_bound(b + 1, b + _ + 1, x1[i]) - b;
		x2[i] = std::lower_bound(b + 1, b + _ + 1, x2[i]) - b;
		y1[i] = std::lower_bound(b + 1, b + _ + 1, y1[i]) - b;
		y2[i] = std::lower_bound(b + 1, b + _ + 1, y2[i]) - b;
	}
	addedge(1, 2, k, 0);
	for (int i = 1; i <= _ * 2; i++) addedge(i + 1, i + 2, INF, 0);
	for (int i = 1; i <= n; i++)
		if (x1[i] != x2[i])
			addedge(x1[i] * 2 + 1, x2[i] * 2, 1, -len[i]);
		else
			addedge(x1[i] * 2, x1[i] * 2 + 1, 1, -len[i]);
	ek(1, _ * 2 + 2, x, y);
	printf("%d", -y);
}