#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>

const int N = 1e4 + 41, M = 1e5 + 51;

struct {
	int to, next;
} e[M << 1];
int head[N], cnt;
void addedge(int x, int y) { e[++cnt] = {y, head[x]}, head[x] = cnt; }

int dfn[N], low[N], ins[N], col[N], w[N], nw[N], idx, scnt;
std::stack<int> st;
void dfs(int x) {
	x[dfn] = x[low] = ++idx, x[ins] = 1, st.push(x);
	for (int i = x[head], nx; i; i = e[i].next)
		if (!(nx = e[i].to)[dfn])
			dfs(nx), x[low] = std::min(x[low], nx[low]);
		else if (nx[ins])
			x[low] = std::min(x[low], nx[dfn]);
	if (x[dfn] == x[low])
		for (int y = scnt++; !st.empty();) {
			y = st.top(), st.pop(), y[ins] = 0;
			y[col] = scnt, scnt[nw] += y[w];
			if (y == x) break;
		}
}

int dp[N];
int dfs2(int x) {
	if (x[dp]) return x[dp];
	for (int i = x[head]; i; i = e[i].next) x[dp] = std::max(x[dp], dfs2(e[i].to));
	return x[dp] += x[nw];
}

int n, m, ans, x[M], y[M];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", i + w);
	for (int i = 1; i <= m; i++) scanf("%d%d", x + i, y + i), addedge(x[i], y[i]);
	for (int i = 1; i <= n; i++)
		if (!i[dfn]) dfs(i);
	memset(head, 0, sizeof head), cnt = 0;
	for (int i = 1; i <= m; i++)
		if (x[i][col] != y[i][col]) addedge(x[i][col], y[i][col]);
	for (int i = 1; i <= scnt; i++)
		if (!i[dp]) ans = std::max(ans, dfs2(i));
	printf("%d", ans);
}