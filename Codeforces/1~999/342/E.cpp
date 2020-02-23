#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51, INF = 0x3f3f3f3f;

// clang-format off
#define L ch][0
#define R ch][1
int ch[N][2], p[N], sz[N], v[N], tag[N], mn[N];
void up(int x) { x[mn] = std::min({x[L][mn], x[v], x[R][mn]}), x[sz] = x[L][sz] + x[R][sz] + 1; }
bool c(int x) { return x[p][R] == x; }
void put(int x, int y) { if (x) x[tag] = std::min(x[tag], y), x[mn] = std::min(x[mn], y), x[v] = std::min(x[v], y - 2 * x[L][sz]); }
void pd(int x) { put(x[L], x[tag]), put(x[R], x[tag] - 2 * (x[L][sz] + 1)), x[tag] = INF; }
bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = x[ch][!k];
	(nr(y) && (ch[z][c(y)] = x)), p[p[p[ch[ch[x][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
void pa(int x) { if (nr(x)) pa(x[p]); pd(x); }
void sp(int x) { pa(x); for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) == c(y) ? y : x), 0); }
void ac(int x) { for (int i = 0; x; x = (i = x)[p]) sp(x), x[R] = i, up(x); }
// clang-format on

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int dep[N];
void dfs(int x, int par, int d) {
	x[p] = par, x[dep] = d;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != par) dfs(nx, x, d + 1);
}

int n, q, op, x, y;
signed main() {
	0 [v] = 0 [mn] = 0 [tag] = INF;
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) i[v] = i[mn] = i[tag] = INF, i[sz] = 1;
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	1 [mn] = 1 [v] = -1;
	dfs(1, 0, 1);
	while (q--) {
		scanf("%d%d", &op, &x);
		ac(x), sp(x);
		if (op == 1)
			put(x, x[dep] - 2);
		else
			printf("%d\n", x[mn] + x[dep]);
	}
}