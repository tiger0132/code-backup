#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define int long long

const int N = 3e5 + 53;

struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, x[head], z}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head], z}, y[head] = cnt;
}

struct node {
	int x, d;
	bool operator<(const node& r) const { return d > r.d; }
};

std::priority_queue<node> pq;
int n, dis[N], pre[N], pid[N];
void spfa() {
	for (int i = 2; i <= n; i++) i[dis] = 1e16;
	for (pq.push({1, 0}); !pq.empty();) {
		node t = pq.top();
		pq.pop();
		int x = t.x, d = t.d;
		if (d != x[dis]) continue;
		for (int i = x[head], nx; i; i = e[i].next)
			if ((nx = e[i].to)[dis] > x[dis] + e[i].w)
				nx[pre] = x, nx[pid] = (i + 1) / 2, nx[dis] = x[dis] + e[i].w,
				pq.push({nx, nx[dis]});
	}
}

int m, k, x, y, z;
void dfs(int x, int p) {
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p && k > 0) printf("%lld ", e[i].w), k--, dfs(nx, x);
}
signed main() {
	for (scanf("%lld%lld%lld", &n, &m, &k); m--;)
		scanf("%lld%lld%lld", &x, &y, &z), addedge(x, y, z);
	spfa();
	memset(head, 0, sizeof head), cnt = 0;
	for (int i = 2; i <= n; i++) addedge(i[pre], i, i[pid]);
	printf("%lld\n", std::min(n - 1, k));
	dfs(1, 0);
}