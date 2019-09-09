#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e6 + 62, M = 26;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

struct state {
	int len, link, nxt[M];
} st[N];
int last, sz, s[N];
void init() { sz = last = 1; }
void ins(int c) {
	int cur = ++sz;
	st[cur].len = st[last].len + 1, cur[s]++;
	int p = last, q, cl;
	for (; p && !(q = st[p].nxt[c]); p = st[p].link) st[p].nxt[c] = cur;
	if (!p)
		st[cur].link = 1;
	else if (st[p].len + 1 == st[q].len)
		st[cur].link = q;
	else {
		cl = ++sz;
		st[cl] = {st[p].len + 1, st[q].link, {}};
		memcpy(st[cl].nxt, st[q].nxt, 104);
		for (; p && st[p].nxt[c] == q; p = st[p].link) st[p].nxt[c] = cl;
		st[q].link = st[cur].link = cl;
	}
	last = cur;
}

long long ans;
void dfs(int x) {
	for (int i = x[head], nx; i; i = e[i].next) dfs(nx = e[i].to), x[s] += nx[s];
	if (x[s] != 1) ans = std::max(ans, 1ll * x[s] * st[x].len);
}

char str[N];
int n;
int main() {
	init();
	scanf("%s", str + 1);
	n = strlen(str + 1);
	for (int i = 1; i <= n; i++) ins(str[i] - 'a');
	for (int i = 2; i <= sz; i++) addedge(st[i].link, i);
	dfs(1);
	printf("%lld", ans);
}