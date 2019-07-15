#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>

const int N = 1e2 + 21, M = 5e4 + 45;
struct edge {
	int to, next;
} e[M << 1];
int head[N], in[N], out[N], cnt;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

int dfn[N], low[N], ins[N], col[N], w[N], scnt, idx;
std::stack<int> st;
void dfs(int x) {
	x[dfn] = x[low] = ++idx, x[ins] = 1, st.push(x);
	for (int i = x[head], nx; i; i = e[i].next)
		if (!(nx = e[i].to)[dfn])
			dfs(nx), x[low] = std::min(x[low], nx[low]);
		else if (nx[ins])
			x[low] = std::min(x[low], nx[dfn]);
	if (x[dfn] == x[low]) {
		int y = scnt++;
		do
			y = st.top(), st.pop(), y[ins] = 0, y[col] = scnt, scnt[w]++;
		while (y != x);
	}
}

int n, m, ans, x[M], y[M], p, q;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		while (scanf("%d", &q), q) x[++m] = i, y[m] = q, addedge(i, q);
	for (int i = 1; i <= n; i++)
		if (!i[dfn]) dfs(i);
	p = q = 0;
	for (int i = 1; i <= m; i++)
		if (x[i][col] != y[i][col]) x[i][col][out]++, y[i][col][in]++;
	for (int i = 1; i <= scnt; i++)
		if (!i[in])
			p++;
		else if (!i[out])
			q++;
	if (scnt == 1) return puts("1\n0");
	printf("%d\n%d", p, std::max(p, q));
}