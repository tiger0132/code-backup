#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <queue>

typedef std::pair<int, int> pii;
const int N = 1e5 + 51, M = 3e7 + 73, LN = 18, P = 1e9;

std::vector<std::pair<int, int>> g[N];
struct {
	int fa[N][LN], dep[N], dis[N];
	void ins(int x, int p, int w) {
		x[fa][0] = p, x[dep] = p[dep] + 1, x[dis] = p[dis] + w;
		for (int i = 1; i < LN; i++) x[fa][i] = x[fa][i - 1][fa][i - 1];
	}
	int lca(int x, int y) {
		if (x[dep] < y[dep]) std::swap(x, y);
		for (int i = LN - 1; i >= 0; i--)
			if (x[fa][i][dep] >= y[dep]) x = x[fa][i];
		if (x == y) return x;
		for (int i = LN - 1; i >= 0; i--)
			if (x[fa][i] != y[fa][i]) x = x[fa][i], y = y[fa][i];
		return x[fa][0];
	}
	inline int operator()(int x, int y) { return x[dis] + y[dis] - 2 * lca(x, y)[dis]; }
} dist;

struct Qiuly_AK_IOI {
	std::vector<int> tmp, nod;
	inline void rebuild() {
		sort(tmp.begin(), tmp.end());
		std::vector<int> qwq = nod;
		nod.resize(tmp.size() + qwq.size());
		int i = 0, j = 0, l1 = tmp.size(), l2 = qwq.size();
		while (i < l1 && j < l2)
			(tmp[i] < qwq[j]) ? (nod[i + j] = tmp[i], ++i) : (nod[i + j] = qwq[j], ++j);
		while (i < l1) nod[i + j] = tmp[i], ++i;
		while (j < l2) nod[i + j] = qwq[j], ++j;
		tmp.clear();
	}
	inline int qry(int x) {
		if (tmp.size() >= 275) rebuild();
		int ans = lower_bound(nod.begin(), nod.end(), x + 1) - nod.begin();
		for (int i : tmp) ans += (bool)(i <= x);
		return ans;
	}
	inline void upd(int x) { return tmp.push_back(x); }
	inline void clear() { tmp.clear(), nod.clear(); }
	inline int size() { return tmp.size() + nod.size(); }
} S1[N], S2[N];

int mx[N], sz[N], val[N], dep[N], p[N], rt;
bool vis[N], dfs0_ban[N];
int dfs0(int x, int fa, int lim) {
	x[vis] = false, x[p] = 0;
	x[dep] = 0;
	x[S1].clear(), x[S2].clear();
	int r = 1;
	for (int i = 0, nx; i < x[g].size(); i++)
		if ((nx = x[g][i].first) != fa && !nx[dfs0_ban] && nx[dep] > lim)
			r += dfs0(nx, x, lim);
	return r;
}
void dfs(int x, int fa, int sum) {
	x[sz] = 1, x[mx] = 0;
	for (int i = 0, nx; i < x[g].size(); i++)
		if (!(nx = x[g][i].first)[vis] && nx != fa && !nx[dfs0_ban]) {
			dfs(nx, x, sum), x[sz] += nx[sz];
			x[mx] = std::max(x[mx], nx[sz]);
		}
	x[mx] = std::max(x[mx], sum - x[sz]);
	if (!rt || x[mx] < rt[mx]) rt = x;
}
void dfs2(int x, int fa, int d, int t) {
	t[S1].upd(d - x[val]);
	if (t[p]) t[S2].upd(dist(x, t[p]) - x[val]);
	x[sz] = 1;
	for (int i = 0, nx; i < x[g].size(); i++)
		if (!(nx = x[g][i].first)[vis] && nx != fa && !nx[dfs0_ban])
			dfs2(nx, x, d + x[g][i].second, t), x[sz] += nx[sz];
}
void divi(int x, int sum) {
	x[vis] = true;
	for (int i = 0, nx; i < x[g].size(); i++)
		if (!(nx = x[g][i].first)[vis] && !nx[dfs0_ban]) {
			int ns = nx[sz] < x[sz] ? nx[sz] : sum - x[sz];
			rt = 0, dfs(nx, x, ns);
			rt[p] = x;
			rt[dep] = x[dep] + 1;
			dfs2(rt, 0, 0, rt);
			divi(rt, ns);
		}
}
void rebuild(int x) {
	int xp = x[p];
	for (int i = xp; i; i = i[p]) i[dfs0_ban] = true;
	int sub_sz = dfs0(x, xp, xp[dep]);
	xp[vis] = true;
	rt = 0, dfs(x, xp, sub_sz);
	rt[p] = xp, rt[dep] = xp[dep] + 1;
	dfs2(rt, 0, 0, rt), divi(rt, sub_sz);
	for (int i = xp; i; i = i[p]) i[dfs0_ban] = false;
	xp[vis] = false;
}
void upd(int x, int r) {
	x[vis] = true;
	for (int cur = x, f; f = cur[p], cur; cur = f) {
		cur[S1].upd(dist(cur, x) - r);
		if (f) cur[S2].upd(dist(f, x) - r);
	}
	int y = 0;
	for (int i = x; i[p]; i = i[p])
		if (i[S1].size() > i[p][S1].size() * 0.8) y = i[p];
	if (y) rebuild(y);
}
int qry(int x, int r) {
	int ret = 0;
	for (int cur = x, last = 0; cur; last = cur, cur = cur[p]) {
		int d = dist(x, cur);
		ret += cur[S1].qry(r - d);
		if (last) ret -= last[S2].qry(r - d);
	}
	return ret;
}

int n, m, x, y, z, col[N];
long long la;
char op[2];
int main() {
	scanf("%*d%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &x, &y, &z), x ^= la % P;
		i[val] = z;
		if (i == 1) {
			i[S1].upd(-z);
			puts("0");
			continue;
		}
		x[g].push_back({i, y});
		i[g].push_back({x, y});
		i[p] = x, i[dep] = x[dep] + 1;
		dist.ins(i, x, y);
		printf("%lld\n", la += qry(i, z));
		upd(i, z);
	}
}