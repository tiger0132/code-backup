#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long L;
const int N = 2e6 + 62;
struct edge {
	int to, next;
} e[N];
int head[N], cnt;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

int len[N], link[N], tr[N][26], sz[N], nc, last;
void ins(int c) {
	int cur = ++nc;
	cur[len] = last[len] + 1;
	int p = last, q, cl;
	for (; p && !(q = p[tr][c]); p = p[link]) p[tr][c] = cur;
	if (!p)
		cur[link] = 1;
	else if (p[len] + 1 == q[len])
		cur[link] = q;
	else {
		cl = ++nc;
		cl[len] = p[len] + 1, cl[link] = q[link];
		memcpy(cl[tr], q[tr], sizeof *tr);
		for (; p && p[tr][c] == q; p = p[link]) p[tr][c] = cl;
		q[link] = cur[link] = cl;
	}
	cur[sz] = 1, last = cur;
}

L ans;
void dfs(int x) {
	for (int i = x[head], nx; i; i = e[i].next) dfs(nx = e[i].to), x[sz] += nx[sz];
	if (x[sz] != 1) ans = std::max(ans, 1ll * x[sz] * x[len]);
}

char ch;
signed main() {
	nc = last = 1;
	while ((ch = getchar()) != '\n') ins(ch - 'a');
	for (int i = 2; i <= nc; i++) addedge(i[link], i);
	dfs(1);
	printf("%lld", ans);
}