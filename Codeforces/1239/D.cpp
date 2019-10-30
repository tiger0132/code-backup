#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>

const int N = 1e6 + 61;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

int dfn[N], low[N], col[N], sz[N], ins[N], sc, idx;
std::stack<int> st;
void dfs(int x) {
	x[dfn] = x[low] = ++idx, x[ins] = true, st.push(x);
	for (int i = x[head], nx; i; i = e[i].next)
		if (!(nx = e[i].to)[dfn])
			dfs(nx), x[low] = std::min(x[low], nx[low]);
		else if (nx[ins])
			x[low] = std::min(x[low], nx[dfn]);
	if (x[dfn] == x[low])
		for (int y = (++sc)[sz] = 0; !st.empty() && y != x;)
			(y = st.top())[col] = sc, sc[sz]++, st.pop();
}

int t, n, m, f, x[N], y[N], d[N];
int main() {
	for (scanf("%*d"); ~scanf("%d%d", &n, &m);) {
		for (int i = 1; i <= m; i++) scanf("%d%d", x + i, y + i), addedge(x[i], y[i]);
		for (int i = 1; i <= n; i++)
			if (!i[dfn]) dfs(i);
		for (int i = 1; i <= m; i++)
			if (x[i] != y[i]) y[i][d]++;
		for (int i = 1; i <= sc; i++)
			if (!i[d]) f = i;
		if (sc == 1 || !f) {
			puts("No");
			continue;
		}
		printf("Yes\n%d %d\n", n - f[sz], f[sz]);
		for (int i = 1; i <= n; i++)
			if (i[col] != f) printf("%d ", i);
		puts("");
		for (int i = 1; i <= n; i++)
			if (i[col] == f) printf("%d ", i);
		puts("");
		memset(head, 0, (n + 1) * 4), memset(d, 0, (n + 1) * 4), sc = idx = cnt = f = 0;
	}
}