#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <stack>

const int N = 2e3 + 32;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void $(int x, int y) { e[++cnt] = (edge){y, head[x]}, head[x] = cnt; }
static int dfn[N], low[N], vis[N], col[N], scnt, idx;
std::stack<int> st;
void dfs(int x) {
	dfn[x] = low[x] = ++idx, vis[x] = 1, st.push(x);
	for (int i = head[x], nx; i; i = e[i].next) {
		if (!dfn[nx = e[i].to]) dfs(nx);
		if (!dfn[nx] || vis[nx]) low[x] = std::min(low[x], low[nx]);
	}
	if (dfn[x] == low[x])
		for (int _ = scnt++; !st.empty();) {
			_ = st.top(), st.pop(), vis[_] = 0, col[_] = scnt;
			if (_ == x) break;
		}
}

char s1[N], s2[N];
int _, n, m;
int main() {
	for (scanf("%d", &_); _--;) {
		memset(head, 0, sizeof head), cnt = scnt = idx = 0;
		memset(low, 0, sizeof low);
		memset(dfn, 0, sizeof dfn);
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			scanf("%s%s", s1, s2);
			int u = 0, v = 0, p = *s1 == 'h', q = *s2 == 'h';
			for (int j = 1; isdigit(s1[j]); j++) u = u * 10 + s1[j] - 48;
			for (int j = 1; isdigit(s2[j]); j++) v = v * 10 + s2[j] - 48;
			$(u + !p * n, v + q * n), $(v + !q * n, u + p * n);
		}
		for (int i = 1; i <= 2 * n; ++i)
			if (!dfn[i]) dfs(i);
		for (int i = 1; i <= n; i++)
			if (col[i] == col[i + n]) goto end;
		puts("GOOD");
		if (0)
		end:
			puts("BAD");
	}
}