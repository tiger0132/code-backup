// "constructive algorithms" with 2700 is terrible!

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 2e5 + 52;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt = 1;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}

struct dsu {
	int p[N];
	int f(int x) { return p[x] ? p[x] = f(p[x]) : x; }
	void m(int x, int y) {
		if ((x = f(x)) != (y = f(y))) p[x] = y;
	}
} _;

int a[N], v[N], c[N], d[N], P[N];
void dfs(int x, int p) {
	for (int i = head[x], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p)
			c[nx] = !c[x], d[nx] = d[x] + 1, P[nx] = x, dfs(nx, x), v[x] -= v[nx], a[i / 2] += v[nx], v[nx] = 0;
}

int n, m, x[N], y[N], a0[N], v0[N];
bool f[N];
signed main() {
	scanf("%I64d%I64d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%I64d", v + i);
	for (int i = 1; i <= m; i++) {
		scanf("%I64d%I64d", x + i, y + i);
		if (_.f(x[i]) != _.f(y[i]))
			f[i] = true, addedge(x[i], y[i]), _.m(x[i], y[i]);
		else
			cnt += 2;
	}
	c[1] = 1, dfs(1, 0);
	if (v[1] % 2) return puts("NO"), 0;
	if (!v[1]) {
		puts("YES");
		for (int i = 1; i <= m; i++) printf("%I64d\n", a[i]);
		return 0;
	}
	memcpy(a0, a, sizeof a), memcpy(v0, v, sizeof v);
	for (int i = 1, s, t; i <= m; i++) {
		if (f[i] || c[s = x[i]] != c[t = y[i]]) continue;
		int val = v[1] / 2;
		v[s] -= val, v[t] -= val, a[i] += val, dfs(1, 0);
		if (v[1]) {
			memcpy(a, a0, sizeof a), memcpy(v, v0, sizeof v);
			v[s] += val, v[t] += val, a[i] -= val, dfs(1, 0);
		}
		puts("YES");
		for (int j = 1; j <= m; j++) printf("%I64d\n", a[j]);
		return 0;
	}
	puts("NO");
}