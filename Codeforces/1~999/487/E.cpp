#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <stack>

const int N = 2e5 + 52;

// clang-format off
struct graph {
	struct { int to, next; } e[N << 1];
	int head[N], cnt;
	void addedge(int x, int y) { e[++cnt] = {y, x[head]}, x[head] = cnt, e[++cnt] = {x, y[head]}, y[head] = cnt; }
} s, t;
#define L ch][0
#define R ch][1
int p[N], ch[N][2], r[N], v[N], mn[N], st[N], top;
std::multiset<int> ss[N];
void up(int x) {
	x[mn] = x[v];
	if (x[L]) x[mn] = std::min(x[mn], x[L][mn]);
	if (x[R]) x[mn] = std::min(x[mn], x[R][mn]);
}
bool c(int x) { return x[p][R] == x; }
bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
void rv(int x) { std::swap(x[L], x[R]), x[r] ^= 1; }
void pd(int x) { r[x] && (rv(x[L]), rv(x[R]), r[x] = 0); }
void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = x[ch][!k];
	(nr(y) && (z[ch][c(y)] = x)), p[p[p[ch[x[ch][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
void sp(int x) {
	for (int i = st[top = 1] = x; nr(i); i = i[p]) st[++top] = i[p];
	while (top) pd(st[top--]);
	for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) ^ c(y) ? x : y), 0);
}
int ac(int x) { int i = 0; for (; x; x = (i = x)[p]) sp(x), x[R] = i, up(x); return i; }
void mr(int x) { ac(x), sp(x), rv(x); }
void spl(int x, int y) { mr(x), ac(y), sp(y); }
void lnk(int x, int y) { mr(x), x[p] = y, up(y); }
int lca(int x, int y) { ac(x); return ac(y); }
// clang-format on

int n, dfn[N], low[N], par[N], top2, dc, idx;
std::stack<int> stk;
void dfs1(const graph& gs, graph& gt, int x) {
	x[dfn] = x[low] = ++idx, stk.push(x);
	for (int i = x[gs.head], nx; i; i = gs.e[i].next)
		if (!(nx = gs.e[i].to)[dfn]) {
			dfs1(gs, gt, nx);
			x[low] = std::min(x[low], nx[low]);
			if (nx[low] == x[dfn]) {
				gt.addedge(x, ++dc);
				for (int y = 0; y != nx;) gt.addedge(y = stk.top(), dc), stk.pop();
			}
		} else
			x[low] = std::min(x[low], nx[dfn]);
}
void dfs2(const graph& g, int x, int f) {
	for (int i = x[g.head], nx; i; i = g.e[i].next)
		if ((nx = g.e[i].to) != f) {
			nx[par] = x;
			lnk(x, nx);
			dfs2(g, nx, x);
			if (x > n) x[ss].insert(nx[v]);
		}
	if (x > n) x[v] = *x[ss].begin();
}

int m, q, x, y;
char op[2];
int main() {
	scanf("%d%d%d", &n, &m, &q), dc = n;
	for (int i = 1; i <= n; i++) scanf("%d", i + v), i[mn] = i[v];
	for (int i = 1; i <= m; i++) scanf("%d%d", &x, &y), s.addedge(x, y);
	dfs1(s, t, 1);
	dfs2(t, 1, -1);
	while (q--) {
		scanf("%s%d%d", op, &x, &y);
		if (*op == 'A') {
			mr(1);
			int l = lca(x, y), ans;
			spl(x, y), ans = y[mn];
			if (l > n) ans = std::min(ans, l[par][v]);
			printf("%d\n", ans);
		} else {
			if (x[par]) {
				sp(x[par]);
				x[par][ss].erase(x[par][ss].lower_bound(x[v]));
				x[par][ss].insert(x[v] = y);
				x[par][v] = *x[par][ss].begin();
				up(x[par]);
			} else
				x[v] = y;
			sp(x), up(x);
		}
	}
}