#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>

const int N = 1e4 + 41, M = 1e5 + 51;

struct edge {
	int to, next;
} e[M << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int dfn[N], low[N], ins[N], cut[N], ccnt, idx;
std::stack<int> st;
void dfs(int x, int rt) {
	x[dfn] = x[low] = ++idx, st.push(x), x[ins] = 1;
	for (int i = x[head], nx, c = 0; i; i = e[i].next)
		if (!(nx = e[i].to)[dfn]) {
			dfs(nx, rt), x[low] = std::min(x[low], nx[low]);
			if (nx[low] >= x[dfn] && ++c > (x == rt)) ccnt += !x[cut], x[cut] = 1;
		} else if (nx[ins])
			x[low] = std::min(x[low], nx[dfn]);
}

int n, m, x, y;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d", &x, &y), addedge(x, y);
	for (int i = 1; i <= n; i++)
		if (!i[dfn]) dfs(i, i);
	printf("%d\n", ccnt);
	for (int i = 1; i <= n; i++)
		if (i[cut]) printf("%d ", i);
}