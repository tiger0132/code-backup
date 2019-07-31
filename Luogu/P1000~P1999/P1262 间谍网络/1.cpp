#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>

const int N = 3e3 + 33, M = 2e4 + 42;
struct edge {
	int to, next;
} e[M << 1];
int head[N], in[N], out[N], cnt;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

int dfn[N], low[N], ins[N], col[N], nw[N], id[N], w[N], scnt, idx;
std::stack<int> st;
void dfs(int x) {
	x[dfn] = x[low] = ++idx, x[ins] = 1, st.push(x);
	for (int i = x[head], nx; i; i = e[i].next)
		if (!(nx = e[i].to)[dfn])
			dfs(nx), x[low] = std::min(x[low], nx[low]);
		else if (nx[ins])
			x[low] = std::min(x[low], nx[dfn]);
	if (x[dfn] == x[low]) {
		int y = ++scnt;
		scnt[id] = x, scnt[nw] = x[w];
		do {
			y = st.top(), st.pop(), y[ins] = 0, y[col] = scnt;
			scnt[nw] = std::min(scnt[nw], y[w]), scnt[id] = std::min(scnt[id], y);
		} while (y != x);
	}
}

int vis[N], ccnt;
void dfs2(int x) {
	if (x[vis]) return;
	x[vis] = 1, ccnt++;
	for (int i = head[x]; i; i = e[i].next) dfs(e[i].to);
}

int n, k, m, ans, x[N], y[N], p, q;
int main() {
	memset(w, 0x3f, sizeof w);
	for (scanf("%d%d", &n, &k); k--;) scanf("%d%d", &p, &q), p[w] = std::min(p[w], q);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) scanf("%d%d", x + i, y + i), addedge(x[i], y[i]);
	for (int i = 1; i <= n; i++)
		if (!i[dfn]) dfs(i);
	memset(head, 0, sizeof head), cnt = 0;
	for (int i = 1; i <= m; i++)
		if (x[i][col] != y[i][col]) addedge(x[i][col], y[i][col]), y[i][col][in]++;
	for (int i = 1; i <= scnt; i++) {
		if (!i[in]) {
			if (i[nw] == 0x3f3f3f3f) {
				printf("NO\n%d", i[id]);
				return 0;
			}
			ans += i[nw];
			dfs2(i);
		}
	}
	if (scnt == 1) return puts("1\n0");
	printf("YES\n%d", ans);
}