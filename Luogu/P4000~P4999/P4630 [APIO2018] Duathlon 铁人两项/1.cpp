#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>

typedef long long ll;
const int N = 2e5 + 52, M = 4e5 + 54;

struct graph {
	struct {
		int to, next;
	} e[M << 1];
	int head[N], cnt;
	void addedge(int x, int y) { e[++cnt] = {y, x[head]}, x[head] = cnt, e[++cnt] = {x, y[head]}, y[head] = cnt; }
} s, t;

int dfn[N], low[N], w[N], idx, dc, nc;
std::stack<int> st;
void dfs(int x) {
	x[dfn] = x[low] = ++idx, nc++, st.push(x);
	for (int i = x[s.head], nx; i; i = s.e[i].next)
		if (!(nx = s.e[i].to)[dfn]) {
			dfs(nx);
			x[low] = std::min(x[low], nx[low]);
			if (nx[low] == x[dfn]) {
				t.addedge(x, ++dc), dc[w]++;
				for (int y = 0; y != nx; st.pop()) t.addedge(y = st.top(), dc), dc[w]++;
			}
		} else
			x[low] = std::min(x[low], nx[dfn]);
}

int n, sz[N];
ll ans;
void dfs2(int x, int p) {
	x[sz] = x <= n;
	for (int i = x[t.head], nx; i; i = t.e[i].next)
		if ((nx = t.e[i].to) != p) dfs2(nx, x), ans += 1ll * x[w] * x[sz] * nx[sz], x[sz] += nx[sz];
	ans += 1ll * x[w] * x[sz] * (nc - x[sz]);
}

int m, x, y;
int main() {
	for (scanf("%d%d", &n, &m); m--;) {
		scanf("%d%d", &x, &y);
		s.addedge(x, y);
	}
	memset(w + 1, -1, n * 4);
	for (int i = 1; i <= n; i++)
		if (!i[dfn]) {
			for (int j = n + 1; j <= dc; j++) j[t.head] = j[w] = 0;
			dc = n, nc = t.cnt = 0;
			dfs(i);
			dfs2(i, 0);
			while (!st.empty()) st.pop();
		}
	printf("%lld", ans * 2);
}