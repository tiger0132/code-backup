#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define $ for (int i = x[head], nx; i; i = e[i].next)
#define _nx (nx = e[i].to)

const int N = 1e5 + 51;
struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, x[head], z}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head], z}, y[head] = cnt;
}

int col[N], par[N], vis[N], pt, pv, ans, a2, mxdep;
std::vector<int> v;
void upd(int x) {
	if (x > ans) ans = x, a2 = 0;
	a2 += x == ans;
}
void dfs1(int x, int p, int d, int *arr) {  // 最远点
	x[par] = p, x[arr] = d;
	if (x[col] && d > pv) pv = d, pt = x;
	$ if (_nx != p) dfs1(nx, x, d + e[i].w, arr);
}
int dfs2(int x, int p, int d) {  // 处理子树
	if (x[col]) mxdep = std::max(mxdep, d);
	int c = x[col];
	$ if (_nx != p && !nx[vis]) c += dfs2(nx, x, d + e[i].w);
	if (!x[col]) upd(c);
	return c;
}

int n, x, y, z, s, t, disL[N], disR[N], L[N], R[N], sz[N], dep[N], sL, sR;
std::vector<int> lnk;
int main() {
	for (scanf("%d%d", &n, &x); x--;) scanf("%d", &y), y[col] = 1;
	for (int i = 1; i < n; i++) scanf("%d%d%d", &x, &y, &z), addedge(x, y, z);
	dfs1(1, 0, 0, disL), s = pt, pv = -1;
	dfs1(s, 0, 0, disL), t = pt, pv = -1;
	dfs1(t, 0, 0, disR);
	for (int i = s; i; i = i[par]) lnk.push_back(i), i[vis] = 1;
	for (int i : lnk) mxdep = -1, i[sz] = dfs2(i, 0, 0), x[dep] = mxdep;
	for (int i : lnk) {
		if (x[dep] == i[disR]) break;
		if (i[disL] < i[disR]) i[R] += i[sz], sR += i[sz];
	}
	std::reverse(lnk.begin(), lnk.end());
	for (int i : lnk) {
		if (x[dep] == i[disL]) break;
		if (i[disL] > i[disR]) i[L] += i[sz];
	}
	for (int i : lnk) {
		sR -= i[R];
		if (!i[col]) upd(sL + sR + i[sz]);
		sL += i[L];
	}
	printf("%d %d", ans, a2);
}