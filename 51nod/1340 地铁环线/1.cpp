#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define int long long
#define mid (l + r) / 2

const int N = 55, M = 3e3 + 33;

struct edge {
	int to, next, op, w;
} e[M << 1];
int head[N], cnt;
void addedge(int x, int y, int z, int w) {
	e[++cnt] = (edge){y, x[head], w, z}, x[head] = cnt;
}
void addlt(int a, int b, int c, int op) {  // a - b <= c
	addedge(b, a, c, op);
}
void addgt(int a, int b, int c, int op) {  // a - b >= c
	addlt(b, a, -c, -op);
}

int n, dis[N], vis[N], c[N], pre[N], prew[N], coef[N];
bool dfsv[N];
int dfs(int x, int c) {
	x[coef] = c, x[dfsv] = true;
	if (x[pre][dfsv]) return c + x[prew] - x[pre][coef];
	return dfs(x[pre], c + x[prew]);
}
int spfa() {
	memset(dis, 0x3f, sizeof dis);
	memset(vis, 0, sizeof vis);
	memset(c, 0, sizeof c);

	std::queue<int> q;
	for (int i = 1; i <= n; i++) q.push(i);
	for (int x; !q.empty(); q.pop()) {
		vis[x = q.front()] = 0;
		for (int i = x[head], nx; i; i = e[i].next)
			if ((nx = e[i].to)[dis] > x[dis] + e[i].w) {
				nx[pre] = x, nx[prew] = e[i].op;
				nx[dis] = x[dis] + e[i].w;
				if (!nx[vis]) {
					nx[vis] = 1;
					if (++nx[c] > n + 1) {
						memset(dfsv, 0, sizeof dfsv);
						int t = dfs(nx, 0);
						return t ? t : -1;
					}
					q.push(nx);
				}
			}
	}
	return 0;
}

int a1[N], b1[N], d1[N];
int a2[N], b2[N], d2[N];
int m1, m2;
int check(int k) {
	memset(head, 0, sizeof head), cnt = 0;
	for (int i = 1; i < n; i++) addgt(i + 1, i, 1, 0);
	addlt(n, 1, k - 1, 1);
	for (int i = 1; i <= m1; i++)
		if (a1[i] < b1[i])
			addgt(b1[i], a1[i], d1[i], 0);
		else
			addlt(a1[i], b1[i], k - d1[i], 1);
	for (int i = 1; i <= m2; i++)
		if (a2[i] < b2[i])
			addlt(b2[i], a2[i], d2[i], 0);
		else
			addgt(a2[i], b2[i], k - d2[i], 1);
	return spfa();
}
signed main() {
	for (scanf("%*d"); ~scanf("%lld%lld%lld", &n, &m1, &m2);) {
		for (int i = 1; i <= m1; i++)
			scanf("%lld%lld%lld", a1 + i, b1 + i, d1 + i), a1[i]++, b1[i]++;
		for (int i = 1; i <= m2; i++)
			scanf("%lld%lld%lld", a2 + i, b2 + i, d2 + i), a2[i]++, b2[i]++;

		int ansl, ansr, l, r;

		l = n, r = 1e12;
		while (l <= r)
			if (check(mid) >= 0)
				l = mid + 1;
			else
				r = mid - 1;
		ansr = l;

		l = n, r = 1e12;
		while (l <= r)
			if (check(mid) <= 0)
				r = mid - 1;
			else
				l = mid + 1;
		ansl = l;

		if (ansr > 9e11)
			puts("-1");
		else
			printf("%lld\n", ansr - ansl);
	}
}