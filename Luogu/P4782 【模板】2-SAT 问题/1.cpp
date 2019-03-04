#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>

const int N = 2e6 + 62;
struct edge {
	int to, next;
} e[N << 1];
static int head[N], cnt;
inline void addedge(int x, int y) { e[++cnt] = (edge){y, head[x]}, head[x] = cnt; }

static int dfn[N], low[N], vis[N], col[N], scnt, idx;
std::stack<int> st;
void dfs(int x) {
	dfn[x] = low[x] = ++idx, vis[x] = 1;
	st.push(x);
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (!dfn[nx]) {
			dfs(nx);
			low[x] = std::min(low[x], low[nx]);
		} else if (vis[nx])
			low[x] = std::min(low[x], low[nx]);
	}
	if (dfn[x] == low[x]) {
		for (scnt++; !st.empty();) {
			int _ = st.top();
			st.pop(), vis[_] = 0, col[_] = scnt;
			if (_ == x) break;
		}
	}
}

int n, m, x, a, y, b;
int main() {
	register int i;
	for (scanf("%d%d", &n, &m); m--;) {
		scanf("%d%d%d%d", &x, &a, &y, &b);
		addedge(x + !a * n, y + b * n);
		addedge(y + !b * n, x + a * n);
	}
	for (i = 1; i <= 2 * n; i++)
		if (!dfn[i]) dfs(i);
	for (i = 1; i <= n; i++)
		if (col[i] == col[n + i]) return puts("IMPOSSIBLE"), 0;
	puts("POSSIBLE");
	for (i = 1; i <= n; i++) printf("%d ", col[i] > col[n + i]);
}