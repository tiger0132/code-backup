#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e5 + 51, M = 2e5 + 52;
struct edge {
	int to, next, w;
} e[M << 1];
int head[N], cnt = 0;
void addedge(int x, int y, int z) { e[++cnt] = (edge){y, x[head], z}, x[head] = cnt; }

int n, m, s;
int dis[N];
struct node {
	int x, d;
	bool operator<(const node& rhs) const { return d > rhs.d; }
};
std::priority_queue<node> pq;
void spfa() {
	memset(dis, 0x3f, (n + 1) * 4), dis[s] = 0;
	for (pq.push((node){s, 0}); !pq.empty();) {
		node t = pq.top();
		pq.pop();
		int x = t.x, d = t.d;
		if (d != x[dis]) continue;
		for (int i = head[x], nx; i; i = e[i].next)
			if ((nx = e[i].to)[dis] > x[dis] + e[i].w)
				nx[dis] = x[dis] + e[i].w, pq.push((node){nx, nx[dis]});
	}
}

int x, y, z;
int main() {
	scanf("%d%d%d", &n, &m, &s);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z);
	}
	spfa();
	for (int i = 1; i <= n; i++) printf("%d ", dis[i]);
}