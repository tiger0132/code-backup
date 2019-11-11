#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>

const int N = 1e6 + 61;

int dfn[N], low[N], ins[N], col[N], w[N], idx, scnt;
std::vector<int> list[N], out, g[N];
std::stack<int> st;
void dfs(int x) {
	x[dfn] = x[low] = ++idx, x[ins] = 1, st.push(x);
	for (int nx : g[x])
		if (!nx[dfn])
			dfs(nx), x[low] = std::min(x[low], nx[low]);
		else if (nx[ins])
			x[low] = std::min(x[low], nx[dfn]);
	if (x[dfn] == x[low])
		for (int y = scnt++ & 0; y != x && !st.empty();)
			y = st.top(), st.pop(), y[ins] = 0, y[col] = scnt, scnt[w]++,
			scnt[list].push_back(y);
}

int n, m, u[N], v[N], id[N], d[N];
bool cmp(int x, int y) { return u[x] < u[y] || (u[x] == u[y] && v[x] < v[y]); }

int x, y, l, pre[N], suf[N];
void del(int x) {
	x[pre][suf] = x[suf];
	x[suf][pre] = x[pre];
}

std::queue<int> q;
bool vis[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (scanf("%d", &x); x--;)
			scanf("%d", &y), g[i].push_back(y), u[++m] = i, v[m] = y;
	for (int i = 1; i <= n; i++)
		if (!i[dfn]) dfs(i);
	for (int i = 1; i <= m; i++) u[i] = u[i][col], v[i] = v[i][col], id[i] = i;
	std::sort(id + 1, id + m + 1, cmp);
	for (int i = 1; i <= n; i++) g[i].clear();
	n = scnt;
	for (int i = 0; i <= n; i++) i[pre] = i - 1, i[suf] = i + 1;
	n[suf] = 0;
	for (int i = l = 1; i <= m; i++)
		if (id[i][u] != id[l][u] || id[i][v] != id[l][v]) {
			if (i - l == 1ll * id[l][u][w] * id[l][v][w])
				g[id[l][u]].push_back(id[l][v]), id[l][v][d]++;
			l = i;
		}
	if (m + 1 - l == 1ll * id[l][u][w] * id[l][v][w])
		g[id[l][u]].push_back(id[l][v]), id[l][v][d]++;
	for (int i = 1; i <= n; i++)
		if (!i[d]) del(i), q.push(i);
	for (int x; !q.empty(); q.pop()) {
		x = q.front();
		for (int i : x[list]) out.push_back(i);
		for (int nx : g[x]) nx[vis] = 1;
		for (int p = 0 [suf]; p; p = p[suf])
			if (!p[vis]) del(p), q.push(p);
		for (int nx : g[x]) nx[vis] = 0;
	}
	std::sort(out.begin(), out.end());
	printf("%d", out.size());
	for (int i : out) printf(" %d", i);
}