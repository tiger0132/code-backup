#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e6 + 61, M = 26;

struct graph {
	struct edge {
		int to, next;
	} e[N << 1];  // 4n
	int head[N], cnt;
	void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }
};

struct state {
	int len, link, nxt[M];
} st[N];  // 2n
int last, sz;
ll sub[N];
void init() { last = sz = 1; }
void ins(int c) {
	int cur = ++sz, p = last, q, cl;
	for (st[cur].len = st[p].len + 1, cur[sub]++; p && !(q = st[p].nxt[c]);
		 p = st[p].link)
		st[p].nxt[c] = cur;
	if (!p)
		st[cur].link = 1;
	else if (st[p].len + 1 == st[q].len)
		st[cur].link = q;
	else {
		st[cl = ++sz] = {st[p].len + 1, st[q].link, {}};
		memcpy(st[cl].nxt, st[q].nxt, sizeof(int[M]));
		for (; p && st[p].nxt[c] == q; p = st[p].link) st[p].nxt[c] = cl;
		st[cur].link = st[q].link = cl;
	}
	last = cur;
}

ll dp[N], dp2[N];
int v[N];
void dfs1(const graph& g, int x) {
	for (int i = x[g.head], nx = x[v] = 1; i; i = g.e[i].next)
		((nx = g.e[i].to)[v] != 1 && (dfs1(g, nx), 0)), x[sub] += nx[sub];
}
void dfs2(const graph& g, int x) {
	x[dp] = 1, x[dp2] = x[sub], x[v] = 2;
	for (int i = x[g.head], nx; i; i = g.e[i].next)
		((nx = g.e[i].to)[v] != 2 && (dfs2(g, nx), 0)), x[dp] += nx[dp],
			x[dp2] += nx[dp2];
}
#define DEF_SOLVE(id, mode, ofs)                                 \
	void solve##id(int x, int k) {                               \
		if (!k) return;                                          \
		for (int i = 0, nx; i < M; i++)                          \
			if ((nx = st[x].nxt[i]) && k <= nx[mode])            \
				return putchar(i + 'a'), solve##id(nx, k - ofs); \
			else                                                 \
				k -= nx[mode];                                   \
		exit(puts("-1") & 0);                                    \
	}
DEF_SOLVE(0, dp, 1)
// DEF_SOLVE(1, dp2, x[sub])
void solve1(int x, int k) {
	if (!k) return;
	for (int i = 0, nx; i < M; i++)
		if ((nx = st[x].nxt[i]) && k <= nx[dp2])
			return putchar(i + 'a'), solve1(nx, k - nx[sub]);
		else
			k -= nx[dp2];
	exit(puts("-1") & 0);
}

int t, k, n;
graph g, h;
char s[N];
int main() {
	init();
	scanf("%s%d%d", s + 1, &t, &k);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++) ins(s[i] - 'a');
	for (int i = 2; i <= sz; i++) g.addedge(st[i].link, i);
	for (int i = 1; i <= sz; i++)
		for (int j = 0; j < M; j++)
			if (st[i].nxt[j]) h.addedge(i, st[i].nxt[j]);
	dfs1(g, 1), dfs2(h, 1);
	(t ? solve1 : solve0)(1, k);
}