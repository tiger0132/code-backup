#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

typedef std::pair<int, int> pii;
typedef long long L;
const int N = 1e5 + 51;

std::vector<pii> g[N];
int p[N], sz[N];
int fd(int x) { return x[p] ? x[p] = fd(x[p]) : x; }
void mg(int x, int y) {
	if ((x = fd(x)) != (y = fd(y))) {
		if (x[sz] > y[sz]) std::swap(x, y);
		x[p] = y, y[sz] += x[sz];
	}
}

L dS[N], dT[N], dP[N];
int fa[N];
void dfs(int x, int p, L *dis) {
	for (auto [nx, w] : x[g])
		if (nx != p) nx[fa] = x, nx[dis] = x[dis] + w, dfs(nx, x, dis);
}

int n, q, S, T, P, id[N];
L mx, mn, mi, f[N], l;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) id[i] = i;
	for (int i = 1, x, y, z; i < n; i++) {
		scanf("%d%d%d", &x, &y, &z);
		x[g].emplace_back(y, z);
		y[g].emplace_back(x, z);
	}
	dfs(1, 0, dS), mx = 0;
	for (int i = 1; i <= n; i++)
		if (i[dS] > mx) mx = i[dS], S = i;

	memset(dS, 0, sizeof dS);
	dfs(S, 0, dS), mx = 0;
	for (int i = 1; i <= n; i++)
		if (i[dS] > mx) mx = i[dS], T = i;

	dfs(T, 0, dT), mn = 2e18;
	for (int i = 1; i <= n; i++) {
		f[i] = std::max(i[dS], i[dT]);
		if (llabs(i[dS] - i[dT]) < mn) mn = llabs(i[dS] - i[dT]), P = i;
	}

	dfs(P, 0, dP);
	std::sort(id + 1, id + n + 1,
			  [](int x, int y) { return f[x] < f[y] || (f[x] == f[y] && x < y); });
	for (scanf("%d", &q); q--;) {
		scanf("%lld", &l);
		int ans = 0;
		for (int i = 1; i <= n; i++) i[sz] = 1, i[p] = 0;
		for (int i = n, j = n; i >= 1; i--) {
			for (; f[id[j]] - f[id[i]] > l; j--) fd(id[j])[sz]--;
			ans = std::max(ans, fd(id[i])[sz]);
			mg(id[i], fa[id[i]]);
		}
		printf("%d\n", ans);
	}
}