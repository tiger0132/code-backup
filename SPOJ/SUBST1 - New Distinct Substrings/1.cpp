#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 2e6 + 62, M = 26;
struct edge {
	int to, next;
} e[N << 1];	   // 4n
int head[N], cnt;  // 2n
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

struct state {
	int len, link, nxt[M];
} st[N];  // 2n
int sz, last;
void init() { memset(st, 0, sizeof(state) * (sz + 1)), last = sz = 1; }
void ins(int c) {
	int cur = ++sz, p = last, q, cl;
	st[cur].len = st[last].len + 1;
	for (; p && !(q = st[p].nxt[c]); p = st[p].link) st[p].nxt[c] = cur;
	if (!p)
		st[cur].link = 1;
	else if (st[p].len + 1 == st[q].len)
		st[cur].link = q;
	else {
		st[cl = ++sz] = {st[p].len + 1, st[q].link, {}};
		memcpy(st[cl].nxt, st[q].nxt, sizeof(int[M]));
		for (; p && st[p].nxt[c] == q; p = st[p].link) st[p].nxt[c] = cl;
		st[q].link = st[cur].link = cl;
	}
	last = cur;
}
ll dp[N];
void dfs(int x) {
	for (int i = x[head]; i; i = e[i].next)
		(dp[e[i].to] || (dfs(e[i].to), 0)), x[dp] += 1 + e[i].to[dp];
}

char s[N];
int n;
int main() {
	for (scanf("%*d"); ~scanf("%s", s + 1);) {
		memset(head, 0, sizeof head), memset(dp, 0, sizeof dp), cnt = 0, init(),
																n = strlen(s + 1);
		for (int i = 1; i <= n; i++) ins(s[i] - 'a');
		for (int i = 1; i <= sz; i++)
			for (int j = 0; j < M; j++)
				if (st[i].nxt[j]) addedge(i, st[i].nxt[j]);
		dfs(1);
		printf("%lld\n", dp[1]);
	}
}