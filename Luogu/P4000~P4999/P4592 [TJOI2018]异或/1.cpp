#include <algorithm>
#include <cstdio>
#include <cstring>

#define _(x) x = cl(x)
#define L ch][0
#define R ch][1
const int N = 6e6 + 66, K = 1 << 30;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int ch[N][2], s[N], nc;
int cl(int x) { return (++nc)[L] = x[L], nc[R] = x[R], nc[s] = x[s], nc; }
void ins(int x, int k, int v) { x[s]++, (k && (ins(_(x[ch][!!(v & k)]), k / 2, v), 0)); }
int qry(int x1, int x2, int k, int v) {
	int t = !(k & v);
	if (!k) return 0;
	return x1[ch][t][s] < x2[ch][t][s] ? qry(x1[ch][t], x2[ch][t], k / 2, v) | k
									   : qry(x1[ch][!t], x2[ch][!t], k / 2, v);
}

int v[N], src[N], rt[N], dep[N], par[N], dfn[N], top[N], sz[N], son[N], idx;
void dfs1(int x, int p, int d) {
	x[par] = p, x[sz] = 1, x[dep] = d;
	for (int i = x[head], nx, mx = 0; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs1(nx, x, d + 1), x[sz] += nx[sz];
			if (nx[sz] > mx) x[son] = nx, mx = nx[sz];
		}
}
void dfs2(int x, int t) {
	x[dfn] = ++idx, idx[v] = x[src], x[top] = t;
	if (!x[son]) return;
	dfs2(x[son], t);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par] && nx != x[son]) dfs2(nx, nx);
}
int qry(int x, int y, int z) {
	int ans = 0;
	for (; x[top] != y[top]; x = x[top][par]) {
		if (x[top][dep] < y[top][dep]) std::swap(x, y);
		ans = std::max(ans, qry((x[top][dfn] - 1)[rt], x[dfn][rt], K, z));
	}
	if (x[dep] > y[dep]) std::swap(x, y);
	return std::max(ans, qry((x[dfn] - 1)[rt], y[dfn][rt], K, z));
}

int n, q, op, x, y, z;
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", src + i);
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	dfs1(1, 0, 1), dfs2(1, 1);
	for (int i = 1; i <= n; i++) ins(i[rt] = cl((i - 1)[rt]), K, i[v]);
	while (q--) {
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1)
			printf("%d\n", qry((x[dfn] - 1)[rt], (x[dfn] + x[sz] - 1)[rt], K, y));
		else
			scanf("%d", &z), printf("%d\n", qry(x, y, z));
	}
}