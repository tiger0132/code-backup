#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <utility>

const int N = 1e5 + 51;
struct edge {
	int to, next;
} e[N << 1];
int head[N], deg[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt, deg[x]++;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt, deg[y]++;
}

int sz[N], mst[N] = {999999999}, rt, n;
void dfs1(int x, int p, int d) {
	sz[x] = 1, mst[x] = 0;
	for (int i = head[x], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs1(nx, x, d + 1), sz[x] += sz[nx], mst[x] = std::max(mst[x], sz[nx]);
	mst[x] = std::max(mst[x], n - sz[x]);
	if (mst[x] < mst[rt]) rt = x;
}

std::map<int, std::pair<int, int>> mp;
int dfs2(int x, int p, int d) {
	if (deg[x] == 1) return mp[d].first++, mp[d].second = x;
	if (deg[x] > 2) return 0;
	for (int i = head[x], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) return dfs2(nx, x, d + 1);
}

int a[N];
void dfs3(int x, int p, int d) {
	if (a[d] && a[d] != deg[x]) exit(!printf("-1"));
	if (!a[d]) a[d] = deg[x];
	for (int i = head[x], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs3(nx, x, d + 1);
}

int main() {
	for (int i = (scanf("%d", &n), 1), x, y; i < n; i++, addedge(x, y)) scanf("%d%d", &x, &y);
	dfs1(1, 0, 1);
	for (int i = head[rt]; i; i = e[i].next) dfs2(e[i].to, rt, 1);
	for (auto i : mp)
		if (i.second.first == 1) rt = i.second.second;
	dfs3(rt, 0, 1), printf("%d", rt);
}