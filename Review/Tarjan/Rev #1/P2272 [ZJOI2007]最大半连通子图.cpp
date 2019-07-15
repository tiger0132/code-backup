#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <stack>

typedef long long ll;
const int N = 1e5 + 51, M = 1e6 + 61;
struct edge {
	int to, next;
} e[M << 1];
int head[N], cnt, p;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

int dfn[N], low[N], ins[N], col[N], w[N], scnt, idx;
std::stack<int> st;
void dfs(int x) {
	x[dfn] = x[low] = ++idx, st.push(x), x[ins] = 1;
	for (int i = x[head], nx; i; i = e[i].next)
		if (!(nx = e[i].to)[dfn])
			dfs(nx), x[low] = std::min(x[low], nx[low]);
		else if (nx[ins])
			x[low] = std::min(x[low], nx[dfn]);
	if (x[dfn] == x[low])
		for (int y = scnt++; !st.empty();) {
			y = st.top(), st.pop(), y[ins] = 0, y[col] = scnt, scnt[w]++;
			if (y == x) break;
		}
}

int dp[N], dp2[N];
int dfs2(int x) {
	if (x[dp]) return x[dp];
	for (int i = x[head], nx; i; i = e[i].next)
		if (dfs2(nx = e[i].to) > x[dp])
			x[dp] = nx[dp], x[dp2] = nx[dp2];
		else if (x[dp] == nx[dp])
			x[dp2] = (x[dp2] + nx[dp2]) % p;
	x[dp2] = (x[dp2] + !x[dp]) % p;
	return x[dp] += x[w];
}

int n, m, x[M], y[M], mx, my;
std::set<ll> s;
ll id(int u, int v) { return (u - 1ll) * n + v; }
int main() {
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 1; i <= m; i++) scanf("%d%d", x + i, y + i), addedge(x[i], y[i]);
	for (int i = 1; i <= n; i++)
		if (!i[dfn]) dfs(i);
	memset(head, 0, sizeof head), cnt = 0;
	for (int i = 1; i <= m; i++)
		if (x[i][col] != y[i][col] && !s.count(id(x[i][col], y[i][col])))
			addedge(x[i][col], y[i][col]), s.insert(id(x[i][col], y[i][col]));
	for (int i = 1; i <= scnt; i++)
		if (dfs2(i) > mx)
			mx = i[dp], my = i[dp2];
		else if (i[dp] == mx)
			my = (my + i[dp2]) % p;
	printf("%d\n%d", mx, my);
}