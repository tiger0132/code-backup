#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>

const int N = 2e5 + 52;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt, deg[N];
void addedge(int x, int y, int f = 0) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt, y[deg] += f;
}

int dfn[N], low[N], ins[N], col[N], scnt, idx;
std::vector<int> scc[N];
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
			y = st.top(), st.pop(), scc[scnt].push_back(y), y[col] = scnt, y[ins] = 0;
			if (y == x) break;
		}
}

int n, k, a[N], b[N];
std::vector<int> ord;
std::queue<int> q;
char ans[N];
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) scanf("%d", b + i);
	for (int i = 1; i < n; i++) addedge(a[i], a[i + 1]), addedge(b[i], b[i + 1]);
	for (int i = 1; i <= n; i++)
		if (!i[dfn]) dfs(i);
	memset(head, 0, sizeof head), cnt = 0;
	for (int i = 1; i < n; i++) {
		if (a[i][col] != a[i + 1][col]) addedge(a[i][col], a[i + 1][col], 1);
		if (b[i][col] != b[i + 1][col]) addedge(b[i][col], b[i + 1][col], 1);
	}
	for (int i = 1; i <= scnt; i++)
		if (!i[deg]) q.push(i);
	for (; !q.empty(); q.pop())
		for (int x = q.front(), i = x[head], nx = (ord.push_back(x), 1); i; i = e[i].next)
			if (!--(nx = e[i].to)[deg]) q.push(nx);
	if (ord.size() < k) return puts("NO"), 0;
	for (int i = 0; i < ord.size(); i++)
		for (int j : ord[i][scc]) ans[j] = std::min(122, 97 + i);
	puts("YES");
	puts(ans + 1);
}