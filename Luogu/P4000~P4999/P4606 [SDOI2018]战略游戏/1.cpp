#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#define M(x) memset(x, 0, sizeof(x))

const int N = 1e6 + 53;

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) { e[++cnt] = {y, x[head]}, x[head] = cnt, e[++cnt] = {x, y[head]}, y[head] = cnt; }

int n, p[N], d[N], sz[N], son[N], top[N], dis[N], dfn[N], idx;
void dfs1(int x) {
	x[dis] = x[p][dis] + (x <= n), x[sz] = 1;
	for (int i = x[head], nx, mx = 0; i; i = e[i].next)
		if ((nx = e[i].to) != x[p]) {
			nx[p] = x, nx[d] = x[d] + 1, dfs1(nx), x[sz] += nx[sz];
			if (nx[sz] > mx) x[son] = nx, mx = nx[sz];
		}
}
void dfs2(int x, int t) {
	x[top] = t, x[dfn] = ++idx;
	if (!x[son]) return;
	dfs2(x[son], t);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[p] && nx != x[son]) dfs2(nx, nx);
}
int lca(int x, int y) {
	for (; x[top] != y[top]; x = x[top][p])
		if (x[top][d] < y[top][d]) std::swap(x, y);
	return x[d] < y[d] ? x : y;
}

int low[N], cut[N], dcnt;
std::vector<int> dcc[N];
std::stack<int> st;
void dfs(int x) {
	x[dfn] = x[low] = ++idx, st.push(x);
	for (int i = x[head], nx; i; i = e[i].next)
		if (!(nx = e[i].to)[dfn]) {
			dfs(nx);
			x[low] = std::min(x[low], nx[low]);
			if (nx[low] == x[dfn]) {
				int y = 0;
				dcc[++dcnt].clear(), dcc[dcnt].push_back(x);
				while (y != nx) dcc[dcnt].push_back(y = st.top()), st.pop();
			}
		} else
			x[low] = std::min(x[low], nx[dfn]);
}
int query(int x, int y) {
	int l = lca(x, y);
	return x[dis] + y[dis] - 2 * l[dis];
}

#define DCC(x) x + n
int m, k, x, y, a[N], ans;
int main() {
	for (scanf("%*d"); ~scanf("%d%d", &n, &m);) {
		M(head), M(dfn), M(low), M(son), M(cut), dcnt = cnt = 0, idx = 0;
		while (m--) scanf("%d%d", &x, &y), addedge(x, y);
		while (!st.empty()) st.pop();
		dfs(1);
		M(head), cnt = 0, idx = 0;
		for (int i = 1; i <= dcnt; i++)
			for (int j : dcc[i]) addedge(j, DCC(i));
		dfs1(1), dfs2(1, 1);
		for (scanf("%d", &m); m--;) {
			scanf("%d", &k), ans = 0;
			for (int i = 1; i <= k; i++) scanf("%d", a + i);
			std::sort(a + 1, a + k + 1, [](int x, int y) { return x[dfn] < y[dfn]; });
			for (int i = 1; i <= k; i++) ans += query(a[i], a[i % k + 1]);
			printf("%d\n", ans / 2 - k + (lca(a[1], a[k]) <= n));
		}
	}
}