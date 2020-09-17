#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 5e3 + 35, M = 5e4 + 45, INF = 0x3f3f3f3f;
struct edge {
	int to, next, w, c;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z, int w) {
	e[++cnt] = (edge){y, x[head], z, w}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head], 0, -w}, y[head] = cnt;
}

int dis[N], pre[N], flow[N];
bool vis[N];
void ek(int s, int t, int &f, int &c) {
	std::queue<int> q;
	while (t[dis] != INF) {
		memset(pre, 0, sizeof pre);
		memset(vis, 0, sizeof vis);
		memset(flow, 0, sizeof flow);
		memset(dis, 0x3f, sizeof dis);
		s[flow] = INF, s[dis] = 0;
		for (q.push(s); !q.empty(); q.pop())
			for (int x = q.front(), i = x[head], nx = x[vis] = false; i; i = e[i].next)
				if ((nx = e[i].to)[dis] > x[dis] + e[i].c && e[i].w) {
					nx[dis] = x[dis] + e[i].c;
					nx[flow] = std::min(x[flow], e[i].w);
					nx[pre] = i;
					if (!nx[vis]) nx[vis] = true, q.push(nx);
				}
		for (int i = t[pre]; i; i = e[i ^ 1].to[pre])
			e[i].w -= t[flow], e[i ^ 1].w += t[flow];
		f += t[flow];
		c += t[flow] * t[dis];
	}
}

int n, m, s, t, x, y, z, w, f, c;
int main() {
	scanf("%d%d%d%d", &n, &m, &s, &t);
	while (m--) {
		scanf("%d%d%d%d", &x, &y, &z, &w);
		addedge(x, y, z, w);
	}
	ek(s, t, f, c);
	printf("%d %d\n", f, c);
}