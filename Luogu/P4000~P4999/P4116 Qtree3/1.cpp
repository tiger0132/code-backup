#include <algorithm>
#include <cstdio>
#include <set>

const int N = 1e5 + 51;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}

int dep[N], par[N], sz[N], son[N], top[N], idx;
struct cmp {
	bool operator()(int x, int y) const { return dep[x] < dep[y]; }
};

std::set<int, cmp> sets[N];
void dfs1(int x, int p, int d) {
	dep[x] = d, par[x] = p, sz[x] = 1;
	for (int i = head[x], nx, mx = 0; i; i = e[i].next) {
		if ((nx = e[i].to) == p) continue;
		dfs1(nx, x, d + 1), sz[x] += sz[nx];
		if (sz[nx] > mx) mx = sz[nx], son[x] = nx;
	}
}
void dfs2(int x, int t) {
	if (x == t) sets[x] = std::set<int, cmp>{cmp()};
	top[x] = t;
	if (!son[x]) return;
	dfs2(son[x], t);
	for (int i = head[x], nx; i; i = e[i].next) {
		nx = e[i].to;
		if (nx != par[x] && nx != son[x]) dfs2(nx, nx);
	}
}
int query(int x) {
	int ret = -1;
	for (; top[x]; x = par[top[x]]) {
		if (sets[top[x]].empty()) continue;
		int tmp = *sets[top[x]].begin();
		if (dep[tmp] <= dep[x]) ret = tmp;
	}
	return ret;
}

int n, q, x, y;
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	dfs1(1, -1, 1), dfs2(1, 1);
	while (q--) {
		scanf("%d%d", &x, &y);
		if (x)
			printf("%d\n", query(y));
		else if (sets[top[y]].count(y))
			sets[top[y]].erase(y);
		else
			sets[top[y]].insert(y);
	}
}