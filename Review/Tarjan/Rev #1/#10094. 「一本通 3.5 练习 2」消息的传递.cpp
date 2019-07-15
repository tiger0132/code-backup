#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>

const int N = 1e4 + 41;
int g[N][N], in[N], cnt;

int dfn[N], low[N], ins[N], col[N], w[N], scnt, idx, n;
std::stack<int> st;
void dfs(int x) {
	x[dfn] = x[low] = ++idx, x[ins] = 1, st.push(x);
	for (int nx = 1; nx <= n; nx++)
		if (g[x][nx] && !nx[dfn])
			dfs(nx), x[low] = std::min(x[low], nx[low]);
		else if (g[x][nx] && nx[ins])
			x[low] = std::min(x[low], nx[dfn]);
	if (x[dfn] == x[low]) {
		int y = scnt++;
		do
			y = st.top(), st.pop(), y[ins] = 0, y[col] = scnt, scnt[w]++;
		while (y != x);
	}
}

int ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) scanf("%d", g[i] + j);
	for (int i = 1; i <= n; i++)
		if (!i[dfn]) dfs(i);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (g[i][j] && i[col] != j[col]) j[col][in]++;
	for (int i = 1; i <= scnt; i++) ans += !i[in];
	printf("%d", ans);
}